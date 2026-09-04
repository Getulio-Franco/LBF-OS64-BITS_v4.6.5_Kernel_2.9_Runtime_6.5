#include "libgui.h"
#include "../system/graphics.h"
#include "../gui/wm.h"

/* ============================================================================
* DECLARAÇÕES DE PROTÓTIPOS EXTERNOS E VARIÁVEIS GLOBAIS
* ============================================================================ */
extern void GUI_ComboBox_Rotate(TGUIControl* combo);
extern void GUI_CheckBox_Toggle(TGUIControl* cb);
extern void GUI_RadioButton_Select(TGUIEnvironment* app, TGUIControl* target_rb);
extern void GUI_Edit_SetFocus(TGUIControl* edit);
extern void GUI_Memo_SetFocus(TGUIControl* memo);
extern void GUI_Memo_AddChar(TGUIControl* memo, char key);
extern void GUI_Memo_SetScroll(TGUIControl* memo, int value);

// Variável global de controle de foco do subsistema do Kernel
extern void* g_focused_control;
extern int64_t sys_gui_get_prop(void* handle, int prop);

/* ============================================================================
* GERENCIAMENTO E REGISTRO
* ============================================================================ */
void GUI_InitApplication(TGUIEnvironment* app, int slot_id, const char* title, int w, int h) {
    if (!app) return;
    app->SlotID = slot_id;
    app->ControlCount = 0;
    app->ActiveFocus = NULL;

    app->MainWindow = gui_create_form("MainApp", (char*)title, 1);
    if (app->MainWindow) {
        gui_set_prop(app->MainWindow, PROP_LEFT, 0);
        gui_set_prop(app->MainWindow, PROP_TOP, 0);
        gui_set_prop(app->MainWindow, PROP_WIDTH, w);
        gui_set_prop(app->MainWindow, PROP_HEIGHT, h);
        app->MainWindow->Win.Draggable = true;
        wm_add_window(app->MainWindow);
    }
}

void GUI_RegisterControl(TGUIEnvironment* app, TGUIControl* ctrl, const char* prefix) {
    if (!app || !ctrl || app->ControlCount >= MAX_APP_CONTROLS) return;
    int id = app->ControlCount + 1;
    char id_str[8];
    int idx = 0;
    if (id >= 10) id_str[idx++] = '0' + (id / 10);
    id_str[idx++] = '0' + (id % 10);
    id_str[idx] = '\0';

    strcpy(ctrl->Name, prefix);
    strcat(ctrl->Name, id_str);
    app->Controls[app->ControlCount++] = ctrl;
}

// Função auxiliar para descobrir onde o controle realmente está na tela física
static void GetAbsolutePosition(TGUIControl* ctrl, int* abs_x, int* abs_y) {
    int x = 0;
    int y = 0;
    TGUIControl* current = ctrl;
    while (current != NULL) {
        x += current->Left;
        y += current->Top;
        current = current->Parent;
    }
    *abs_x = x;
    *abs_y = y;
}

/* ============================================================================
* MOTOR CENTRAL DE EVENTOS
* ============================================================================ */
bool GUI_ProcessMouseClick(TGUIEnvironment* app, int mouse_x, int mouse_y) {
    if (!app) return false;

    // Varre de trás para frente (Z-Order)
    for (int i = app->ControlCount - 1; i >= 0; i--) {
        TGUIControl* ctrl = app->Controls[i];
        if (!ctrl) continue;

        int abs_x, abs_y;
        GetAbsolutePosition(ctrl, &abs_x, &abs_y);

        if (mouse_x >= abs_x && mouse_x <= (abs_x + ctrl->Width) &&
            mouse_y >= abs_y && mouse_y <= (abs_y + ctrl->Height)) {

            if (ctrl->Type == TYPE_BUTTON) {
                if (ctrl->OnClick != NULL) ctrl->OnClick(ctrl);
                return true;
            }

            if (ctrl->Type == TYPE_COMBOBOX) {
                GUI_ComboBox_Rotate(ctrl);
                return true;
            }

            if (ctrl->Type == TYPE_CHECKBOX) {
                GUI_CheckBox_Toggle(ctrl);
                return true;
            }

            if (ctrl->Type == TYPE_RADIOBUTTON) {
                GUI_RadioButton_Select(app, ctrl);
                return true;
            }

            // --- COMPONENTE EDIT (TEdit) ---
            if (ctrl->Type == TYPE_EDIT) {
                app->ActiveFocus = ctrl;
                g_focused_control = (void*)ctrl->KernelHandle;
                GUI_Edit_SetFocus(ctrl);
                return true;
            }

            // --- COMPONENTE MEMO (TMemo com tratamento de Scrollbar) ---
            if (ctrl->Type == TYPE_MEMO) {
                app->ActiveFocus = ctrl;
                g_focused_control = (void*)ctrl->KernelHandle;

                int limite_barra_x = abs_x + ctrl->Width - 18;
                if (mouse_x >= limite_barra_x && mouse_x <= (abs_x + ctrl->Width)) {
                    int metade_vertical = abs_y + (ctrl->Height / 2);
                    if (mouse_y < metade_vertical) {
                        GUI_Memo_SetScroll(ctrl, ctrl->ScrollY - 2);
                    } else {
                        GUI_Memo_SetScroll(ctrl, ctrl->ScrollY + 2);
                    }
                } else {
                    GUI_Memo_SetFocus(ctrl);
                }
                return true;
            }

            // --- COMPONENTE SCROLLBAR ---
            if (ctrl->Type == TYPE_SCROLLBAR) {
                int metade_vertical = ctrl->Height / 2;
                int local_y = mouse_y - abs_y;
                int jump = (ctrl->PageSize > 0) ? ctrl->PageSize : 1;

                if (local_y < metade_vertical) {
                    GUI_ScrollBar_SetPosition(ctrl, ctrl->Position - jump);
                } else {
                    GUI_ScrollBar_SetPosition(ctrl, ctrl->Position + jump);
                }
                return true;
            }

            // --- COMPONENTE LISTVIEW ---
            if (ctrl->Type == TYPE_LISTVIEW) {
                app->ActiveFocus = ctrl;
                g_focused_control = (void*)ctrl->KernelHandle;
                TListView* kernel_lv = (TListView*)ctrl->KernelHandle;

                if (kernel_lv) {
                    int local_y = mouse_y - abs_y - 4;
                    int current_scroll = (int)gui_get_prop((void*)ctrl->KernelHandle, PROP_SCROLL_Y);
                    int calculated_index = (local_y / 18) + current_scroll;

                    if (calculated_index < 0) calculated_index = 0;
                    if (calculated_index >= kernel_lv->ItemCount) calculated_index = kernel_lv->ItemCount - 1;

                    kernel_lv->ItemIndex = calculated_index;
                    ctrl->LVItemIndex = calculated_index;

                    if (ctrl->OnItemClick != NULL) {
                        ctrl->OnItemClick(ctrl, calculated_index);
                    }
                }
                return true;
            }

            // =====================================================================
            // --- COMPONENTE WEBPAGE (scroll na barra + clique em link) ---
            // =====================================================================
            if (ctrl->Type == TYPE_WEBPAGE) {
                app->ActiveFocus = ctrl;
                int limite_barra_x = abs_x + ctrl->Width - 18;

                if (mouse_x >= limite_barra_x && mouse_x <= (abs_x + ctrl->Width)) {
                    // Clicou na calha do scroll: sobe/desce 3 linhas
                    int metade = abs_y + (ctrl->Height / 2);
                    int delta = (mouse_y < metade) ? -3 : 3;
                    int novo = ctrl->ScrollY + delta;
                    if (novo < 0) novo = 0;
                    ctrl->ScrollY = novo;
                    gui_set_prop((void*)ctrl->KernelHandle, PROP_SCROLL_Y, (uint64_t)novo);
                } else {
                    // Clicou no conteúdo: mapeia Y -> linha -> link
                    TWebPage* kpg = (TWebPage*)ctrl->KernelHandle;
                    if (kpg && kpg->Doc) {
                        int local_y = mouse_y - abs_y - 5;
                        int line = (local_y / 16) + kpg->ScrollY;
                        if (line >= 0 && line < kpg->Doc->lc) {
                            WebLine* wl = &kpg->Doc->lines[line];
                            if (wl->style == WEB_STYLE_LINK &&
                                wl->link_id >= 0 && wl->link_id < kpg->Doc->kc) {
                                if (ctrl->OnNavigate) {
                                    ctrl->OnNavigate(ctrl, kpg->Doc->links[wl->link_id].url);
                                }
                            }
                        }
                    }
                }
                return true;
            }

            // --- Painel (consome o clique em área vazia) ---
            if (ctrl->Type == TYPE_PANEL) {
                return true;
            }
        }
    }

    // Fora de qualquer controle editável: limpa foco
    app->ActiveFocus = NULL;
    g_focused_control = NULL;
    return false;
}

void GUI_ProcessKeyboard(TGUIEnvironment* app, char key) {
    if (!app || !app->ActiveFocus || key == 0) return;
    TGUIControl* ctrl = app->ActiveFocus;

    // --- TEdit ---
    if (ctrl->Type == TYPE_EDIT) {
        int len = strlen(ctrl->Text);
        if (key == '\b') {
            if (len > 0) ctrl->Text[len - 1] = '\0';
        } else if (key >= 32 && key <= 126 && len < 254) {
            ctrl->Text[len] = key;
            ctrl->Text[len + 1] = '\0';
        }
        gui_set_prop((void*)ctrl->KernelHandle, PROP_CAPTION, (uintptr_t)ctrl->Text);
        if (ctrl->OnChange) ctrl->OnChange(ctrl);
    }
    // --- TMemo ---
    else if (ctrl->Type == TYPE_MEMO) {
        GUI_Memo_AddChar(ctrl, key);
        if (ctrl->OnChange) ctrl->OnChange(ctrl);
    }
}
