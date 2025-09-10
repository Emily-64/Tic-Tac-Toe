# 🎮 Tic-Tac-Toe with Minimax AI

This project is a **C implementation of Tic-Tac-Toe** where the player competes against an **unbeatable AI** powered by the **Minimax adversarial search algorithm**.

---

## 📌 Features
- Play as **X** against the AI (**O**).
- AI uses **Minimax** to always guarantee at least a draw.
- Option to choose whether to **play first or second**.
- Clean board visualization in the terminal.
- Error handling for invalid inputs.

---

## 🧠 Algorithm
The AI is built using the **Minimax algorithm**:
- **Maximizing player (AI)** tries to maximize its score.
- **Minimizing player (Human)** tries to minimize AI’s score.
- Scores:
  - `+10` → AI win  
  - `-10` → Human win  
  - `0` → Draw  
- Minimax explores all possible moves recursively and chooses the optimal one.  

---

## ⚡️ How to Run

### 1. Clone the repository
```bash
git clone https://github.com/your-username/tictactoe-ai.git
cd tictactoe-ai
gcc -O2 -std=c11 tictactoe.c -o tictactoe
./tictactoe
