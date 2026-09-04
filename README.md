# LBF-OS64-BITS_v4.6.5_Kernel_2.9_Runtime_6.5
SISTEMA OPERACIONAL  x86-64 BITS
# 🖥️ LBF-OS 64 Bits — Kernel 2.9 | Runtime 6.5

**Sistema Operacional de 64 bits escrito do zero em C e Assembly x86_64,
com assistente neural portátil integrada: a Existência.**

> *"Nenhum software se faz de um dia para outro, mas alguns nunca deveriam ser perdidos."*

[![Licença](https://img.shields.io/badge/Licen%C3%A7a-GPL--v3-blue.svg)](LICENSE)
[![Linguagem](https://img.shields.io/badge/Linguagem-C%20%7C%20x86__64%20ASM-orange.svg)]()
[![Status](https://img.shields.io/badge/Status-Em%20Desenvolvimento-green.svg)]()

---

## 📖 Sobre o Projeto

O **LBF-OS** é um sistema operacional de 64 bits desenvolvido inteiramente do zero,
sem derivar de Linux, BSD ou qualquer outro kernel existente. Inclui:

- **Kernel 2.8** — modo protegido x86_64, gerenciamento de memória, multitarefa,
  IDT, GDT, FAT32, driver de vídeo, teclado, mouse e IPC entre processos.
- **Runtime 6.5** — camada de execução de aplicativos ELF em Ring 3,
  com SDK gráfico (janelas, botões, edits, memos) e comunicação por IPC.
- **NeuralRuntime** — motor de inteligência artificial portátil escrito em C puro,
  100% independente do sistema operacional.
- **Existência** — assistente neural que calcula, raciocina, lembra, sente,
  aprende e consulta uma biblioteca de conhecimento.

---

## 🧠 NeuralRuntime — A IA Portátil

O NeuralRuntime é o coração inteligente do projeto. Ele foi projetado com um
princípio inviolável: **o núcleo da IA nunca faz syscall de SO, nunca acessa
disco, nunca toca em hardware**. Toda a inteligência vive em C padrão e RAM pura.

Isso significa que o mesmo código dos cores roda em:
- ✅ LBF-OS (integrado)
- ✅ Linux (versão futura)
- ✅ Bare metal
- ✅ Qualquer ambiente com compilador C

### Arquitetura em 3 Camadas

```
┌─────────────────────────────────────────────────┐
│           CAMADA DE INTERAÇÃO (por SO)          │
│  existec.c (LBF-OS) | existelinux.c (futuro)   │
│  Janelas, teclado, mouse, disco — tudo aqui.    │
├─────────────────────────────────────────────────┤
│         DESPACHANTE / ABI ESTÁVEL               │
│  neural.c + neurallib.h                         │
│  Contrato binário: syscalls 100..117            │
│  Regra: adicionar, nunca quebrar.               │
├─────────────────────────────────────────────────┤
│           NÚCLEO PORTÁTIL (sem SO)              │
│  iamath | ialogic | iarouter | iasynth          │
│  iamemory | iaknowledge | iadialog              │
│  iaemotion | ialearn | iareason                 │
│  iapersona | iapattern | iaembed | iafichas     │
│  C puro. Sem malloc. Sem I/O. Sem SO.           │
└─────────────────────────────────────────────────┘
```

### Mapa de Cores (Syscalls)

| Syscall | Core           | Função                                                  |
|---------|----------------|---------------------------------------------------------|
| 100     | `iamath`       | Álgebra ponderada (soma, sub, mult, div)                |
| 101     | `ialogic`      | 7 portas lógicas via MLP de 2 camadas                   |
| 102     | `iarouter`     | Roteador neural: decide qual core ativar                |
| 103     | `iasynth`      | Sintetizador de tom (conversacional × direto)           |
| 104     | `iamemory`     | Memória episódica com reforço Hebbiano                  |
| 105     | `iaknowledge`  | Memória semântica (fatos do mundo)                      |
| 106     | `iadialog`     | Contexto multi-turno ("e mais 3?")                      |
| 107     | `iaemotion`    | Humor, vínculo e energia emocional                      |
| 108     | `ialearn`      | Aprendizado por feedback (ajusta pesos do router)       |
| 109     | `iareason`     | Raciocínio em cadeia ("tenho 10, dei 3, dobrei")        |
| 110     | `iapersona`    | Personalidade e autoconsciência                         |
| 113     | `iapattern`    | Detecção de padrões de uso do usuário                   |
| 116     | `iaembed`      | Mini-cérebro semântico (vetores densos de 16 eixos)     |
| 117     | `iafichas`     | Biblioteca de fichas de conhecimento                    |

### Mini-Cérebro Semântico (iaembed)

O `iaembed` é o salto qualitativo da Existência. Em vez de comparar **letras**
(`strstr`), ela compara **significados** usando vetores densos de 16 eixos
semânticos interpretáveis:

```
Eixos: quantidade | matemática | lógica | pessoa | emoção | comida |
       festa | tempo | lugar | objeto | ação | conhecimento |
       memória | comunicação | natureza | tecnologia
```

**Resultados reais (similaridade × 1000):**

| Par de palavras     | Resultado | Significado                      |
|---------------------|-----------|----------------------------------|
| bolo ~ torta        | 997       | Sinônimos sem letra em comum     |
| capital ~ cidade    | 800       | Mesmo eixo semântico ("lugar")   |
| obrigado ~ valeu    | 1000      | Perfis idênticos                 |
| bolo ~ soma         | 0         | Mundos completamente separados   |

Isso permite que frases como *"capital do brasil"* (sem "qual a") e
*"me fala da torre"* (sem "onde fica", sem "eiffel") sejam compreendidas
corretamente.

### Biblioteca de Fichas (iafichas)

O conhecimento é **dados**, não código. Cada ficha possui:

```
FICHA: ponteiro
  família:    memória
  sinônimos:  [pointer, apontador]
  rótulos:    [memória, básico]
  atributos:  { sintaxe: "int *p = &x;", exemplo: "*p = 10;" }
  texto:      "Variável que guarda o endereço de outra variável..."
```

**5 estratégias genéricas** (o motor não muda ao adicionar fichas):

| Estratégia   | Gatilho                        | Exemplo                              |
|--------------|--------------------------------|--------------------------------------|
| DEFINIR      | "o que é X"                    | `o que e ponteiro`                   |
| RECEITA      | "como usar X"                  | `como usar malloc`                   |
| RECOMENDAR   | "liste X"                      | `liste memoria`                      |
| COMBINAR     | "diferença entre X e Y"        | `diferenca entre stack e heap`       |
| ESCLARECER   | confiança baixa                | Pergunta de volta em vez de chutar   |

**Módulos incluídos:**
- 📘 **Programação em C** — 23 fichas (ponteiros, malloc, struct, ABI, portabilidade...)
- 📗 **História da Computação** — 18 fichas (Babbage, Turing, Ritchie, Linux, software livre...)

Para adicionar um novo módulo: crie um arquivo de dados, registre uma linha no catálogo.
**Zero alteração no motor, na ABI ou no aplicativo.**

---

## 💬 Existência — A Assistente

Em homenagem à assistente pessoal "Existência", criada em Delphi 7 em 2012,
perdida em um HD corrompido e renascida em 2026 com arquitetura neural portátil.

### O que ela sabe fazer

```
Voce: soma 5 3
Existencia: O valor calculado é 8.

Voce: e mais 10
Existencia: O valor calculado é 18.              ← contexto de diálogo

Voce: meu nome e Getulio
Existencia: Guardado na minha memória!

Voce: qual meu nome
Existencia: Eu lembro. Você disse: 'meu nome e Getulio'

Voce: qual a capital do brasil
Existencia: Brasília, a capital federal do Brasil.

Voce: capital do brasil                           ← sem "qual a" (paráfrase)
Existencia: Brasília, a capital federal do Brasil. ← iaembed entendeu!

Voce: o que e ponteiro
Existencia: ponteiro: Variável que guarda o endereço de outra variável...

Voce: como usar malloc
Existencia: malloc: sintaxe: void *p = malloc(n_bytes)...

Voce: quem foi ada lovelace
Existencia: Primeira programadora do mundo...

Voce: tenho 10 dei 3 dobrei
Existencia: [raciocinando] Inicio: 10 | dei 3 -> 7 | dobrei -> 14
            Resposta final: 14                    ← raciocínio em cadeia

Voce: quem e voce
Existencia: Eu sou a Existência: uma assistente neural que calcula,
            lembra, aprende e sente...

Voce: como voce esta
Existencia: Estou bem, obrigada! E você, como está?

Voce: obrigado
Existencia: De nada! Fico muito feliz em ajudar!
            (ajustei meus roteamentos com o seu feedback.)

Voce: o que voce nota em mim
Existencia: Notei que você gosta de cálculos (50% das interações).
```

---

## 📁 Estrutura do Projeto

```
LBF-OS/
├── Kernel/                          # Kernel 2.8 (x86_64)
│   ├── boot/                        # Bootloader
│   ├── system/                      # IDT, GDT, memória, drivers
│   └── ...
│
├── Runtime_Neural/                  # NeuralRuntime 6.5
│   ├── core/                        # Núcleo portátil (sem SO)
│   │   ├── iamath.c / .h           # Álgebra ponderada
│   │   ├── ialogic.c / .h          # Portas lógicas (MLP)
│   │   ├── iarouter.c / .h         # Roteador neural + semântico
│   │   ├── iasynth.c / .h          # Sintetizador de tom
│   │   ├── iamemory.c / .h         # Memória episódica
│   │   ├── iaknowledge.c / .h      # Memória semântica
│   │   ├── iadialog.c / .h         # Contexto multi-turno
│   │   ├── iaemotion.c / .h        # Emoção e vínculo
│   │   ├── ialearn.c / .h          # Aprendizado por feedback
│   │   ├── iareason.c / .h         # Raciocínio em cadeia
│   │   ├── iapersona.c / .h        # Personalidade
│   │   ├── iapattern.c / .h        # Padrões de uso
│   │   ├── iaembed.c / .h          # Mini-cérebro semântico
│   │   ├── iafichas.c / .h         # Motor da Biblioteca
│   │   ├── iafichas_dados.c        # Módulo: Programação em C
│   │   └── iafichas_dados_hist.c   # Módulo: História da Computação
│   │
│   ├── neural/                      # Despachante de syscalls
│   │   ├── neural.c / .h
│   │   └── ...
│   │
│   ├── system_lib/                  # ABI estável
│   │   └── neurallib.h
│   │
│   └── Software/                    # Camada de interação
│       └── existec.c               # Existência (LBF-OS)
│
├── Runtime_sdk/                     # SDK gráfico e IPC
│   ├── sdk/
│   ├── components/
│   └── ...
│
├── RELATORIO_IA.md                  # Relatório técnico da IA
└── README.md                        # Este arquivo
```

---

## 🔧 Como Compilar

### Pré-requisitos

- **GCC Cross-Compiler** (x86_64-elf-gcc) ou GCC nativo para 64 bits
- **NASM** (assembler para os módulos x86_64)
- **Make** (GNU Make)

### Compilação

```bash
# Compilar o Kernel
make kernel

# Compilar o Runtime + NeuralRuntime + Existência
make runtime

# Gerar a imagem do disco (ISO ou IMG)
make image

# Executar no QEMU (teste)
make run
```

### Compilação manual dos cores (referência)

```bash
# Cada core é independente — compila isolado
x86_64-elf-gcc -c -O2 -ffreestanding Runtime_Neural/core/iamath.c -o Runtime_Neural/core/iamath.o
x86_64-elf-gcc -c -O2 -ffreestanding Runtime_Neural/core/iaembed.c -o Runtime_Neural/core/iaembed.o
# ... (um por core)

# Link do ELF da Existência
x86_64-elf-ld -o existec.elf \
    Runtime_Neural/Software/existec.o \
    Runtime_Neural/neural/neural.o \
    Runtime_Neural/core/iamath.o \
    Runtime_Neural/core/ialogic.o \
    Runtime_Neural/core/iarouter.o \
    Runtime_Neural/core/iasynth.o \
    Runtime_Neural/core/iamemory.o \
    Runtime_Neural/core/iaknowledge.o \
    Runtime_Neural/core/iadialog.o \
    Runtime_Neural/core/iaemotion.o \
    Runtime_Neural/core/ialearn.o \
    Runtime_Neural/core/iareason.o \
    Runtime_Neural/core/iapersona.o \
    Runtime_Neural/core/iapattern.o \
    Runtime_Neural/core/iaembed.o \
    Runtime_Neural/core/iafichas.o \
    Runtime_Neural/core/iafichas_dados.o \
    Runtime_Neural/core/iafichas_dados_hist.o
```

---

## 📚 Como Criar um Novo Módulo de Conhecimento

A Biblioteca cresce **sem tocar no motor**. Para adicionar um novo livro:

### 1. Crie o arquivo de dados

```c
// Runtime_Neural/core/iafichas_dados_SEUMODULO.c
#include "iafichas.h"

const Ficha FICHAS_SEUMODULO[] = {
    {"nome do conceito", "familia", {"sinonimo1"}, {"rotulo1","rotulo2"},
     {{"sintaxe","exemplo de uso"},{"cuidado","algo importante"}},
     "Texto descritivo do conceito."},
    // ... mais fichas
};
const int FICHAS_SEUMODULO_TAM = (int)(sizeof(FICHAS_SEUMODULO) / sizeof(FICHAS_SEUMODULO[0]));
```

### 2. Registre no catálogo (`iafichas.c`)

```c
extern const Ficha FICHAS_SEUMODULO[]; extern const int FICHAS_SEUMODULO_TAM;

// Dentro de catalogo_init():
CAT_V[CAT_TAM] = FICHAS_SEUMODULO; CAT_N[CAT_TAM] = FICHAS_SEUMODULO_TAM; CAT_TAM++;
```

### 3. Compile e linke

```bash
x86_64-elf-gcc -c iafichas_dados_SEUMODULO.c -o iafichas_dados_SEUMODULO.o
# Adicione o .o no link do ELF
```

**Pronto.** O motor, a ABI e o aplicativo não mudam. As 5 estratégias
(DEFINIR, RECEITA, RECOMENDAR, COMBINAR, ESCLARECER) funcionam automaticamente
para as novas fichas.

---

## 🎯 Princípios do Projeto

1. **Independência total** — O kernel, o runtime e a IA foram escritos do zero.
   Nenhuma linha de código foi copiada de outro SO.

2. **Portabilidade do núcleo** — Os cores da IA compilam em qualquer ambiente
   com compilador C. Sem `malloc`, sem I/O, sem syscalls de SO.

3. **ABI aditiva** — Novas syscalls não quebram ELFs antigos.
   Adicionar, nunca quebrar.

4. **Conhecimento como dados** — Expandir o que a IA sabe não expande o código.
   Fichas novas = arquivos novos, motor intocado.

5. **Inteligência separada de conhecimento** — O core fornece a inteligência,
   os módulos fornecem o conhecimento, os provedores fornecem o acesso.

6. **Código aberto e livre** — GPL-v3: use, estude, modifique e compartilhe.
   Se derivar, mantenha aberto.

---

## 📜 História

- **2012** — Primeira versão da "Existência" em Delphi 7. Assistente pessoal
  que conversava e tomava decisões baseadas em hardware.
- **20XX** — HD corrompido. O código fonte foi perdido.
- **2026** — Renascimento completo: a Existência renasce em C puro,
  com arquitetura neural portátil, dentro de um SO escrito do zero.
  Desta vez, o código é aberto e nunca mais será perdido.

---

## 🤝 Contribuindo

Contribuições são bem-vindas! Algumas formas de ajudar:

- 📘 **Criar módulos de conhecimento** (fichas) para novos domínios
- 🧠 **Expandir o vocabulário semântico** (`iaembed.c`) com novas palavras
- 🐛 **Reportar bugs** via Issues
- 🔧 **Portar a Existência** para outros ambientes (Linux, SDL, ncurses...)
- 📖 **Melhorar a documentação**

### Regras para contribuir nos cores

- Nunca incluir headers de SO nos arquivos em `Runtime_Neural/core/`
- Nunca usar `malloc`, `printf`, `fopen` ou qualquer função de SO nos cores
- Manter a ABI estável: novas syscalls recebem IDs novos, nunca reutilize
- Testar com rebuild limpo após alterar qualquer `.h`

---

## 📄 Licença

Este projeto é licenciado sob a **GNU General Public License v3.0**.

Você é livre para usar, estudar, modificar e distribuir este software,
desde que qualquer trabalho derivado também seja distribuído sob a mesma licença.

Veja o arquivo [LICENSE](LICENSE) para os termos completos.

---

## 👤 Autor

Desenvolvido com dedicação, uma IA assistente e muitas horas de programação.

> *"O que foi perdido pode renascer melhor.
> O que renasce em liberdade, nunca mais será perdido."*

---

**⭐ Se este projeto te inspirou, deixe uma estrela!**

O projeto segue um princípio simples: > **Pelo povo, para o povo e com o povo.**

Todo o conteúdo pode ser **utilizado, modificado e aprimorado livremente**, sem restrições. A ideia é permitir que qualquer pessoa explore as ferramentas disponíveis, desenvolva seus próprios aplicativos e contribua para a evolução do ecossistema do RING3 Explorer.
