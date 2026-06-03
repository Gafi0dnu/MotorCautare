#Motor de Căutare în Documente Text (C++)

Un motor de căutare minimalist bazat pe consolă, dezvoltat în C++17, capabil să indexeze automat și să caute eficient cuvinte în interiorul unui set de documente text (`.txt`). Proiectul utilizează structuri de date avansate din STL și oferă o interfață grafică colorată direct în consolă.

---

#Caracteristici Principale

* **Indexare Automată:** Scanează un director întreg și încarcă automat toate fișierele cu extensia `.txt`.
* **Suport pentru Diacritice (UTF-8):** Parsează manual caracterele multi-octet specifice limbii române (`ș`, `ț`, `ă`, `î`, `â`) și le convertește în echivalentul lor ASCII fără accent pentru a preveni erorile de runtime.
* **Filtrare Stop-Words:** Optimizează memoria și relevanța căutării prin ignorarea automată a cuvintelor de legătură comune (prepoziții, conjuncții precum *și, sau, la, de, cu*).
* **Căutare Parțială (Substring Match):** Găsește potriviri chiar dacă utilizatorul introduce doar o parte dintr-un cuvânt (ex: căutarea după „baza” va returna și „baze” sau „bazat”).
* **UI Modern în Consolă:** Folosește coduri ANSI Escape pentru a colora textul, facilitând identificarea rapidă a succesului, erorilor și a cuvintelor cheie găsite.

---

##Cerințe de Sistem

* **Compilator:** Compatibil cu **C++17** sau o versiune mai nouă (datorită utilizării bibliotecii `<filesystem>`).
* **Mediu de dezvoltare recomandat:** Visual Studio 2022 / VS Code (cu GCC 9+).
* **Sistem de operare:** Windows 10/11 (codul include activarea nativă a terminalului virtual pentru culori ANSI).

---

##Cum funcționează (Arhitectură)

Proiectul este structurat pe baza a două clase principale:

1.  **`Document`:** Memorează metadatele unui fișier (calea absolută) și conținutul său brut sub formă de string.
2.  **`Index`:** Gestionează motorul de căutare. Inima acestei clase este structura `std::map<std::string, std::set<std::string>>`:
    * **Cheia (String):** Reprezintă cuvântul curățat și normalizat (redus la litere mici, fără punctuație și fără diacritice).
    * **Valoarea (Set):** O listă unică de căi către fișierele în care apare acel cuvânt.

### Fluxul aplicației:
```text
[Director .txt] ➔ [Citire Eficientă (Slurping)] ➔ [Tokenizare & Curățare] ➔ [Indexare în Map] ➔ [Meniu Căutare]# MotorCautare
