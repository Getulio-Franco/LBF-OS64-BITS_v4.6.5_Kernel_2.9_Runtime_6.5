#include "iafichas.h"
#include "iaembed.h"
#include <string.h>

#define FICH_LIMIAR  0.45f
#define FICH_CLAREZA 0.30f
#define MAX_MODULOS  4

/* --- Catálogo da Biblioteca: adicionar um livro = 1 linha aqui --- */
extern const Ficha FICHAS_C[];    extern const int FICHAS_C_TAM;
extern const Ficha FICHAS_HIST[]; extern const int FICHAS_HIST_TAM;

static const Ficha* CAT_V[MAX_MODULOS];
static int          CAT_N[MAX_MODULOS];
static int          CAT_TAM = 0;

static void catalogo_init(void) {
    if (CAT_TAM) return;
    CAT_V[CAT_TAM] = FICHAS_C;    CAT_N[CAT_TAM] = FICHAS_C_TAM;    CAT_TAM++;
    CAT_V[CAT_TAM] = FICHAS_HIST; CAT_N[CAT_TAM] = FICHAS_HIST_TAM; CAT_TAM++;
}

static void cat_lim(char* dst, int cap, const char* src) {
    if (!src) return;
    int i = (int)strlen(dst);
    int j = 0;
    while (src[j] && i < cap - 1) dst[i++] = src[j++];
    dst[i] = '\0';
}

static void para_minusculas(const char* src, char* dst, int cap) {
    int i = 0;
    for (; src[i] && i < cap - 1; i++) {
        char c = src[i];
        dst[i] = (c >= 'A' && c <= 'Z') ? (char)(c + 32) : c;
    }
    dst[i] = '\0';
}

static float ficha_score(const Ficha* f, const char* q, const float* emb_q) {
    if (strstr(q, f->nome)) return 1.0f;
    for (int i = 0; i < 3 && f->sinonimos[i]; i++)
        if (strstr(q, f->sinonimos[i])) return 1.0f;
    float emb_f[EMB_DIM];
    iaembed_frase(f->nome, emb_f);
    return iaembed_cosseno(emb_q, emb_f);
}

int iafichas_consultar(const char* texto, char* out, int out_len) {
    if (!texto || !out || out_len <= 0) return -1;
    out[0] = '\0';
    catalogo_init();

    char q[256];
    para_minusculas(texto, q, sizeof(q));
    float emb_q[EMB_DIM];
    iaembed_frase(q, emb_q);

    int bm = -1, bi = -1, sm = -1, si = -1;
    float s_best = 0.0f, s_sec = 0.0f;
    for (int m = 0; m < CAT_TAM; m++) {
        for (int i = 0; i < CAT_N[m]; i++) {
            float s = ficha_score(&CAT_V[m][i], q, emb_q);
            if (s > s_best)      { s_sec = s_best; sm = bm; si = bi; s_best = s; bm = m; bi = i; }
            else if (s > s_sec)  { s_sec = s; sm = m; si = i; }
        }
    }
    if (bm < 0 || s_best < FICH_CLAREZA) return -1;

    /* ESCLARECER */
    if (s_best < FICH_LIMIAR) {
        cat_lim(out, out_len, "Voce quer saber sobre '");
        cat_lim(out, out_len, CAT_V[bm][bi].nome);
        cat_lim(out, out_len, "'? Tente 'o que e ");
        cat_lim(out, out_len, CAT_V[bm][bi].nome);
        cat_lim(out, out_len, "'.");
        return 4;
    }

    const Ficha* f = &CAT_V[bm][bi];
    int quer_lista = strstr(q,"liste")||strstr(q,"quais")||strstr(q,"me mostre")||strstr(q,"temas");
    int quer_como  = strstr(q,"como")||strstr(q,"exemplo")||strstr(q,"sintaxe");
    int quer_combo = strstr(q,"diferenca")||strstr(q,"versus")||strstr(q," vs ")||strstr(q," entre ");

    /* RECOMENDAR: parentes em TODA a biblioteca */
    if (quer_lista) {
        cat_lim(out, out_len, "Sobre "); cat_lim(out, out_len, f->nome);
        cat_lim(out, out_len, " temos: ");
        int achou = 0;
        for (int m = 0; m < CAT_TAM; m++) {
            for (int i = 0; i < CAT_N[m]; i++) {
                const Ficha* g = &CAT_V[m][i];
                if (g == f) continue;
                int parente = (g->familia && strcmp(g->familia, f->nome) == 0) ||
                              (f->familia && g->familia && strcmp(g->familia, f->familia) == 0);
                if (parente) {
                    if (achou) cat_lim(out, out_len, ", ");
                    cat_lim(out, out_len, g->nome);
                    achou++;
                }
            }
        }
        cat_lim(out, out_len, achou ? "." : ": ainda poucas fichas. Tente 'o que e <tema>'.");
        return 2;
    }

    /* RECEITA */
    if (quer_como) {
        cat_lim(out, out_len, f->nome); cat_lim(out, out_len, ":");
        int tem = 0;
        for (int i = 0; i < 4 && f->atributos[i].chave; i++) {
            cat_lim(out, out_len, " ");
            cat_lim(out, out_len, f->atributos[i].chave);
            cat_lim(out, out_len, ": ");
            cat_lim(out, out_len, f->atributos[i].valor);
            cat_lim(out, out_len, ".");
            tem = 1;
        }
        if (!tem) { cat_lim(out, out_len, " "); cat_lim(out, out_len, f->texto); }
        return 1;
    }

    /* COMBINAR */
    if (quer_combo && sm >= 0 && s_sec >= FICH_LIMIAR) {
        const Ficha* g = &CAT_V[sm][si];
        cat_lim(out, out_len, f->nome); cat_lim(out, out_len, ": ");
        cat_lim(out, out_len, f->texto);
        cat_lim(out, out_len, " | ");
        cat_lim(out, out_len, g->nome); cat_lim(out, out_len, ": ");
        cat_lim(out, out_len, g->texto);
        return 3;
    }

    /* DEFINIR */
    cat_lim(out, out_len, f->nome); cat_lim(out, out_len, ": ");
    cat_lim(out, out_len, f->texto);
    for (int i = 0; i < 4 && f->atributos[i].chave; i++) {
        if (strcmp(f->atributos[i].chave, "exemplo") == 0) {
            cat_lim(out, out_len, " Ex.: ");
            cat_lim(out, out_len, f->atributos[i].valor);
        }
    }
    return 0;
}

int iafichas_contar(void) {
    catalogo_init();
    int n = 0;
    for (int m = 0; m < CAT_TAM; m++) n += CAT_N[m];
    return n;
}
