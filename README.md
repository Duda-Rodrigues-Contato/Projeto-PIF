# Projeto-PIF

[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

---

## 📚 Informações Acadêmicas
**Disciplina**: Programação Imperativa e Funcional (PIF) - 2025.1  
**Instituição de Ensino**: CESAR School  

---

## 👨‍💻 Membros da Equipe
**Maria Eduarda Rodrigues**: [@Duda-Rodrigues-Contato](https://github.com/Duda-Rodrigues-Contato)  
**André Ferraz**: [@afg572](https://github.com/afg572)  
**Jorge Tadeu**: [@tadeuggomes](https://github.com/tadeuggomes)  
**Matheus Melquiades**: [@Ttheusma](https://github.com/Ttheusma)  

---

## 🎮 CyberTerminal Hacker
Um jogo de digitação emocionante onde você defende seu terminal contra ataques hackers digitando palavras que aparecem na tela enquanto evita vírus invasores.

### 🕹️ Como Jogar
- **Objetivo**: Digite corretamente as letras que caem do topo da tela para evitar que os vírus (as letras) atinjam a base do terminal
- **Barra Inferior**:
  - Mostra o tempo decorrido
  - Exibe a quantidade de pontos atual do jogador
  - Mostra a fase em que o jogador se encontra
  - Exibe suas vidas restantes
- **Interação**: Use o teclado para digitar as letras antes que elas desapareçam e tirem suas vidas, cada tentativa de eliminar uma letra errada, remove uma vida do player

### 📊 Níveis de Dificuldade
1. **Nível 1**:
   - Progresso do ataque mais lento.
   - Uma letra por ataque
   - Vírus (letras) descem devagar
2. **Nível 2**:
   - Progresso do ataque moderado.
   - Duas letras por ataque
   - Vírus mais rápidos
3. **Nível 3**:
   - Progresso do ataque acelerado.
   - Três letras por ataque
   - Fase mais difícil com vírus extremamente rápidos

---

## 💻 Compilar e Executar o CyberTerminal Hacker

### 🔧 Como **compilar** o jogo?

Nosso jogo funciona via **terminal** e é compilado com `gcc` utilizando um `Makefile`. Abaixo estão os passos para cada sistema operacional:

#### 💻 Windows (via WSL - Ubuntu)
1. Instale o WSL com Ubuntu:  
   [Guia oficial da Microsoft](https://learn.microsoft.com/pt-br/windows/wsl/install)
2. No Ubuntu (WSL), instale os compiladores:
      - sudo apt update
      - sudo apt install build-essential

#### 🐧 Linux
1. Instale os compiladores necessários:
      - sudo apt update
      - sudo apt install build-essential

#### 🍏 macOS
1. Instale as ferramentas de linha de comando do Xcode:
      - xcode-select --install
---

### 🏃 Como **executar** o jogo?

> Os passos abaixo são iguais para Windows (WSL), Linux e macOS após os compiladores estarem configurados.

1. **Clone o repositório:**

      - git clone https://github.com/Duda-Rodrigues-Contato/Projeto-PIF.git
      - cd Projeto-PIF

2. **Compile o projeto com `make`:**

   ✅ Opção 1 (a partir da raiz do projeto):
  
      - make

   ✅ Opção 2 (dentro da pasta `cli-lib/`):

      - cd cli-lib
      - make run

3. **Execute o jogo:**

   - Se usou a opção 1:
 
      - ./cli-lib/build/bin/CyberTerminalHacker

   - Se usou a opção 2, o `make run` já executa automaticamente.

> 💡 O jogo salvará o `ranking.txt` no diretório atual em que for executado! Além disso, para o funcionamento correto e uma melhor experiência, o terminal deve estar no tamanho máximo

---

### ✅ Exemplo completo no terminal (Linux/WSL/macOS)

   - git clone https://github.com/Duda-Rodrigues-Contato/Projeto-PIF.git
   - cd Projeto-PIF
   - make
   - ./cli-lib/build/bin/CyberTerminalHacker

**Ou:**

   - git clone https://github.com/Duda-Rodrigues-Contato/Projeto-PIF.git
   - cd cli-lib
   - make run

---