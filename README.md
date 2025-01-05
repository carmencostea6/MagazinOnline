# ROCK the SHOP  
**Sistem pentru administrarea unui magazin**

## I. Descriere  
Un magazin online cu produse rock pune la vânzare mai multe categorii de produse și se ocupă cu primirea, procesarea și livrarea comenzilor. Angajații magazinului au responsabilități distincte:  

- **Manager**: se ocupă de managementul stocului de produse.  
- **Operatorii de comenzi**: caută produse în stoc, ambalează și livrează comenzile.  
- **Asistenții**: monitorizează comenzile.  

### Angajați  
- Magazinul are 3 tipuri de angajați: **manager**, **operator comenzi**, **asistent**.  
- Toți angajații au:  
  - **ID unic** (asignat la angajare).  
  - **Nume și prenume** (minim 3 caractere, maxim 30).  
  - **CNP valid**.  
  - **Data angajării**.  

**Calcul salariu:**  
- Salariu de bază: **3500 RON** + **100 RON/an de vechime**.  
- Coeficient de salariu:  
  - Manager: **1.25**  
  - Operator comenzi: **1.00**  
  - Asistent: **0.75**  
- Bonusuri:  
  - Operatorii primesc **0.5% din valoarea comenzilor procesate**.  
  - De ziua lor, angajații (cu excepția managerului) primesc un bonus de **100 RON**.  

**Angajare:**  
- Vârsta minimă: **18 ani**.  
- Posibilitatea modificării numelui unui angajat (ex: în caz de căsătorie).  

**Demisie:**  
- Angajații care demisionează sunt eliminați din evidența magazinului.  

### Produse  
Magazinul vinde 3 tipuri de produse:  
1. **Articole vestimentare**  
   - Caracteristici: culoare, marcă.  
   - Cost suplimentar: **20 RON** pentru împachetare și livrare.  
2. **Discuri (CD-uri și viniluri)**  
   - Caracteristici: casă de discuri, dată lansare, trupă, nume album.  
   - Cost suplimentar: **5 RON** pentru livrare.  
3. **Discuri vintage**  
   - Caracteristici: coeficient raritate (1-5), stare mint.  
   - Cost suplimentar: **15 RON * coeficient raritate**.  

**Operațiuni produse:**  
- Adăugare, ștergere, modificare.  
- Fiecare produs are un **cod unic**.  

**Calcul preț:**  
- Prețul produsului include prețul de bază + costuri suplimentare de livrare.  

### Comenzi  
- Fiecare comandă poate conține:  
  - **Maxim 5 discuri**.  
  - **Maxim 3 articole vestimentare**.  
- Valoarea minimă a comenzii (fără costuri suplimentare): **100 RON**.  
- Comenzile care nu respectă aceste cerințe nu vor fi procesate.  

**Procesare comenzi:**  
- Fiecare comandă este asociată unui operator.  
- Un operator poate gestiona **maxim 3 comenzi în paralel**.  
- Dacă toți operatorii sunt ocupați, comenzile rămân în așteptare.  

---

## II. Funcționalități minimale  

### 1. Gestionare angajați  
- Adăugare, ștergere, modificare, afișare date angajat.  
- Afișarea tuturor angajaților.  
- **Condiție funcționare magazin:**  
  - Minim **1 manager**.  
  - Minim **3 operatori comenzi**.  
  - Minim **1 asistent**.  

### 2. Gestionare produse  
- Adăugare, ștergere, modificare, afișare date produs.  
- Afișarea tuturor produselor din stoc.  
- **Condiție funcționare magazin:**  
  - Minim **2 produse din fiecare tip**.  

### 3. Procesare comenzi  
- Asignarea automată a comenzilor către operatorii de comenzi.  
- Simularea încărcării fiecărui angajat cu cereri.  

### 4. Raportări  
- **Angajatul cu cele mai multe comenzi procesate.**  
- **Top 3 angajați care au gestionat cele mai valoroase comenzi** (inclusiv costuri suplimentare).  
- **Top 3 angajați cu cel mai mare salariu în luna curentă** (ordonați alfabetic după nume și prenume).  
