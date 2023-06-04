/* Estruturas de Dados - Trabalho pratico

Professor: Diego P. Rubert
Aluno(s): Nicolas Leonardo Miranda Lima 

*/

#include <cstdio>
#include <string>

using std::string;

class No
{
  friend class ArvBinBusca;

private:
  int chave;
  No *pai;
  No *esq;
  No *dir;

public:
  No(const int chave);
  void escreve(const char *sep = "");
  int getpai()
  {
    if (this->pai != NULL)
    {
      return this->pai->chave;
    }
    else
      return -1;
  };
  int getesq()
  {
    if (this->esq != NULL)
    {
      return this->esq->chave;
    }
    else
      return -1;
  }
  int getdir()
  {
    if (this->dir != NULL)
    {
      return this->dir->chave;
    }
    else
      return -1;
  }
  int getchave()
  {
    return this->chave;
  }
};

class ArvBinBusca
{
private:
  No *raiz;
  void escreve_ordenado(No *raiz);             // feito
  void escreve(const string &prefixo, No *no); // feito

  No *busca(No *raiz, int chave); // feito
  No *minimo(No *raiz);           // feito
  No *maximo(No *no);             // feito

  void insere(No *no);                        // feito
  void transplante(No *noAntigo, No *noNovo); // feito
  void remove(No *no);                        // feito

  void limpa(No *no); // feito

  void copia(const ArvBinBusca &T); // feito
  void copia(No **dest, No *orig); // feito

public:
  ArvBinBusca(); // feito
  ArvBinBusca(const ArvBinBusca &outro); //feito
  ~ArvBinBusca(); // feito
  ArvBinBusca &operator=(const ArvBinBusca &outro); //feito
  void escreve_ordenado(); // feito
  void escreve();          // feito

  No *get_raiz();          // feito
  No *busca(int chave);    // feito
  No *minimo();            // feito
  No *maximo();            // feito
  No *sucessor(No *no);    // feito
  No *predecessor(No *no); // feito

  void insere(int chave); // feito
  bool remove(int chave); // feito
  void limpa();           // feito
};

int main(void)
{
  ArvBinBusca T; // construtor ArvBinBusca()
  int v[] = {10, 25, 0, 16, 20, 9, 15, 6, 14, 7, 18, 12, 22, 19, 3, 13};
  
  for (const auto &x : v)
    T.insere(x); //TODO: implemente primeiro o metodo insere
  
  printf("T:\n");
  T.escreve();
  printf("Valores de T em ordem crescente: ");
  T.escreve_ordenado(); //TODO: implemente depois escreve_ordenado

  // return 0; //TODO: remover após implementar minimo, maximo, sucessor, predecessor

  No *raiz = T.get_raiz();
  printf("Raiz: ");
  raiz->escreve("\n");

  No *pre = T.predecessor(raiz);
  printf("Predecessor da raiz: ");
  pre->escreve("\n");
  No *suc = T.sucessor(raiz);
  printf("Sucessor da raiz: ");
  suc->escreve("\n");

  printf("Sucessor do predecessor da raiz (== raiz): ");
  T.sucessor(pre)->escreve("\n");
  printf("Predecessor do sucessor da raiz (== raiz): ");
  T.predecessor(suc)->escreve("\n");

  No *minimo = T.minimo();
  No *maximo = T.maximo();
  printf("Mínimo: ");
  minimo->escreve("\n");
  printf("Máximo: ");
  maximo->escreve("\n");

  // return 0; //TODO: remover após implementar remoção

  T.remove(0); // Caso 1
  T.remove(13); // Caso 2
  T.remove(10); // Caso 3b + 3a

  printf("T:\n");
  T.escreve();

  // return 0; //TODO: remover após implementar construtor de cópia e operador de atribuição
  
  ArvBinBusca T2(T); // construtor de cópia
  T2.insere(30);
  printf("T:\n");
  T.escreve();
  printf("T2:\n");
  T2.escreve();

  ArvBinBusca T3 = T; // construtor de cópia
  T3.insere(-8);
  printf("T:\n");
  T.escreve();
  printf("T3:\n");
  T3.escreve();

  T3 = T; // operador de atribuição
  T3.insere(100);
  printf("T:\n");
  T.escreve();
  printf("T3:\n");
  T3.escreve();
  
  return 0;
}

//***********************************
//*** IMPLEMENTAÇÕES DA CLASSE NO ***
//***********************************

No::No(const int chave)
{
  this->chave = chave;
  this->pai = NULL;
  this->esq = NULL;
  this->dir = NULL;
}

void No::escreve(const char *sep)
{
  printf("%2d%s", chave, sep);
}

//********************************************
//*** IMPLEMENTAÇÕES DA CLASSE ARVBINBUSCA ***
//********************************************

No *ArvBinBusca::get_raiz()
{
  return this->raiz;
}

ArvBinBusca::ArvBinBusca()
{
  this->raiz = NULL;
}

ArvBinBusca::ArvBinBusca(const ArvBinBusca &outro)
{
  this->copia(outro);
}

ArvBinBusca::~ArvBinBusca()
{
  this->limpa();
}

ArvBinBusca& ArvBinBusca::operator=(const ArvBinBusca& outro) {
  this->limpa();
  this->copia(outro);
  return *this;
}

void ArvBinBusca::copia(const ArvBinBusca &T)
{
  this->copia(&this->raiz, T.raiz);
}

void ArvBinBusca::copia(No **dest, No *orig)
{
  if (orig == NULL)
  {
    *dest = NULL;
    return;
  }

  *dest = new No(orig->chave);
  (*dest)->pai = orig->pai;

  this->copia(&((*dest)->esq), orig->esq);
  this->copia(&((*dest)->dir), orig->dir);
}

void ArvBinBusca::limpa()
{
  No *raiz = this->get_raiz();
  this->limpa(raiz);
}

void ArvBinBusca::limpa(No *no)
{
  if (no != NULL)
  {
    limpa(no->esq);
    limpa(no->dir);
    delete no;
  }
}

void ArvBinBusca::escreve()
{
  No *raiz = this->get_raiz();
  this->escreve("", raiz);
}

void ArvBinBusca::escreve(const string &prefixo, No *no)
{
  if (no == NULL)
    return;

  bool ehDireito = no->pai && no->pai->dir == no;
  bool temIrmaoEsq = no->pai && no->pai->esq;

  printf(prefixo.c_str());
  printf(ehDireito && temIrmaoEsq ? "├──" : "└──");

  if (no->pai == NULL)
    no->escreve("\n");
  else
    no->escreve(ehDireito ? "d\n" : "e\n");

  this->escreve(prefixo + (ehDireito && temIrmaoEsq ? "│   " : "    "), no->dir);
  this->escreve(prefixo + (ehDireito && temIrmaoEsq ? "│   " : "    "), no->esq);
}

void ArvBinBusca::insere(int chave)
{
  No *novoNo = new No(chave);
  this->insere(novoNo);
}

void ArvBinBusca::insere(No *no)
{
  No *noAuxiliar = NULL;
  No *subArvore = this->raiz;

  while (subArvore != NULL)
  {
    noAuxiliar = subArvore;

    if (no->chave < subArvore->chave)
    {
      subArvore = subArvore->esq;
    }
    else
    {
      subArvore = subArvore->dir;
    }
  }

  no->pai = noAuxiliar;

  if (noAuxiliar == NULL)
  {
    this->raiz = no;
  }
  else
  {
    if (no->chave < noAuxiliar->chave)
    {
      noAuxiliar->esq = no;
    }
    else
    {
      noAuxiliar->dir = no;
    }
  }
}

No *ArvBinBusca::busca(int chave)
{
  No *raiz = this->raiz;
  return this->busca(raiz, chave);
}

No *ArvBinBusca::busca(No *raiz, int chave)
{
  No *noAuxiliar = raiz;
  while (noAuxiliar != NULL)
  {
    if (chave > noAuxiliar->chave)
    {
      noAuxiliar = noAuxiliar->dir;
    }
    else if (chave < noAuxiliar->chave)
    {
      noAuxiliar = noAuxiliar->esq;
    }
    else
    {
      return noAuxiliar;
    }
  }
  return noAuxiliar;
}

No *ArvBinBusca::minimo()
{
  No *raiz = this->raiz;
  return raiz ? this->minimo(raiz) : NULL;
}

No *ArvBinBusca::minimo(No *raiz)
{
  No *noAuxiliar = raiz;
  if (noAuxiliar->esq == NULL)
  {
    return noAuxiliar;
  }
  else
  {
    noAuxiliar = noAuxiliar->esq;
    return this->minimo(noAuxiliar);
  }
}

No *ArvBinBusca::maximo()
{
  No *raiz = this->raiz;
  return raiz ? this->maximo(raiz) : NULL;
}

No *ArvBinBusca::maximo(No *raiz)
{
  No *noAuxiliar = raiz;
  if (noAuxiliar->dir == NULL)
  {
    return noAuxiliar;
  }
  else
  {
    noAuxiliar = noAuxiliar->dir;
    return this->maximo(noAuxiliar);
  }
}

No *ArvBinBusca::sucessor(No *no)
{
  No *subArvore = no;
  if (subArvore->dir != NULL)
  {
    return this->minimo(subArvore->dir);
  }

  No *noAuxiliar = subArvore->pai;
  while (noAuxiliar != NULL && subArvore == noAuxiliar->dir)
  {
    subArvore = noAuxiliar;
    noAuxiliar = noAuxiliar->pai;
  }
  return noAuxiliar;
}

No *ArvBinBusca::predecessor(No *no)
{
  No *subArvore = no;
  if (subArvore->esq != NULL)
  {
    return this->maximo(subArvore->esq);
  }

  No *noAuxiliar = subArvore->pai;
  while (noAuxiliar != NULL && subArvore == noAuxiliar->esq)
  {
    subArvore = noAuxiliar;
    noAuxiliar = noAuxiliar->pai;
  }
  return noAuxiliar;
}

void ArvBinBusca::transplante(No *noAntigo, No *noNovo)
{
  if (noAntigo->pai == NULL)
  {
    this->raiz = noNovo;
  }
  else
  {
    if (noAntigo == noAntigo->pai->esq)
    {
      noAntigo->pai->esq = noNovo;
    }
    else
    {
      noAntigo->pai->dir = noNovo;
    }
  }
  if (noNovo != NULL)
  {
    noNovo->pai = noAntigo->pai;
  }
}

bool ArvBinBusca::remove(int chave)
{
  No *no = this->busca(chave);
  if (no == NULL)
  {
    return false;
  }
  else
  {
    this->remove(no);
    delete no;
    return true;
  }
}

void ArvBinBusca::remove(No *no)
{
  if (no->esq == NULL)
  {
    this->transplante(no, no->dir);
  }
  else
  {
    if (no->dir == NULL)
    {
      this->transplante(no, no->esq);
    }
    else
    {
      No *noAuxiliar = this->minimo(no->dir);
      if (noAuxiliar->pai != no)
      {
        this->transplante(noAuxiliar, noAuxiliar->dir);
        noAuxiliar->dir = no->dir;
        noAuxiliar->dir->pai = noAuxiliar;
      }
      this->transplante(no, noAuxiliar);
      noAuxiliar->esq = no->esq;
      noAuxiliar->esq->pai = noAuxiliar;
    }
  }
}

void ArvBinBusca::escreve_ordenado()
{
  No *raiz = this->raiz;
  this->escreve_ordenado(raiz);
  putchar('\n');
}

void ArvBinBusca::escreve_ordenado(No *raiz)
{
  if (raiz != NULL)
  {
    this->escreve_ordenado(raiz->esq);
    raiz->escreve(" ");
    this->escreve_ordenado(raiz->dir);
  }
}
