#include "trab1.hpp"

vector<vector<string>> vSequencia(26);

vector<double> freqPortugues = {
  0.1463,
  0.0104,
  0.0388,
  0.0499,
  0.1257,
  0.0102,
  0.0130,
  0.0128,
  0.0618,
  0.0040,
  0.0002,
  0.0278,
  0.0474,
  0.0505,
  0.1073,
  0.0252,
  0.0120,
  0.0653,
  0.0781,
  0.0434,
  0.0463,
  0.0167,
  0.0001,
  0.0021,
  0.0001,
  0.0047
};

vector<double> freqIngles = {
  0.08167,
  0.01492,
  0.02782,
  0.04253,
  0.12702,
  0.02228,
  0.02015,
  0.06094,
  0.06966,
  0.00153,
  0.00772,
  0.04025,
  0.02406,
  0.06749,
  0.07507,
  0.01929,
  0.00095,
  0.05987,
  0.06327,
  0.09056,
  0.02758,
  0.00978,
  0.02360,
  0.00150,
  0.01974,
  0.00074
};

/////////////////////////////  1a parte

string normText(string text){
  string ret;
  for(int i = 0;i<text.size();++i){
    if('a' <= text[i] && 'z' >= text[i])
      text[i] -= ('a' - 'A');
    
    ret.push_back(text[i]);
  }
  return ret;
}

string juntText(string texto){
  string ret;
  for(int i = 0;i<texto.size();++i){
    if('a' <= texto[i] && 'z' >= texto[i])
      texto[i] -= ('a' - 'A');
    else if('A' <= texto[i] && 'Z' >= texto[i])
      ret.push_back(texto[i]);
  }
  return ret;
}

string cifrador(string mensagem, string chave){
  string cifrada;
  char aux;
  for(int i = 0, j = 0;i < mensagem.size();++i){
    if('A' <= mensagem[i] && 'Z' >= mensagem[i]){
      aux = ((mensagem[i] - 'A' + chave[j] - 'A')%26) + 'A';
      cifrada.push_back(aux);
      j = (j+1)%chave.size();
    }else
      cifrada.push_back(mensagem[i]);
  }
  return cifrada;
}

string decifrador(string mensagem, string chave){
  string texto;
  char aux;
  for(int i = 0,j = 0;i < mensagem.size();++i){
    if('A' <= mensagem[i] && 'Z' >= mensagem[i]){
      aux = ((mensagem[i] - chave[j])+26)%26 + 'A';
      texto.push_back(aux);
      j = (j+1)%chave.size();
    }else
      texto.push_back(mensagem[i]);
  }
  return texto;
}

//################################################################################//
//                                2a parte                                        //
//################################################################################//

double indCoincid(string mensagem){
  double freq, coincidencia; 
  for(char aux = 'A';aux <= 'Z';++aux){
    int contador = count(mensagem.begin(), mensagem.end(), aux);
    freq += contador*contador - contador;
  }
  coincidencia = freq/(mensagem.length()*mensagem.length() - mensagem.length());
  return coincidencia;
}

char frequencia(string fatia, int idioma){
  vector<double> X2(26), aux2, freqIdioma;

  if(idioma == 1)
    freqIdioma = freqIngles;
  else
    freqIdioma = freqPortugues;

  for(int i = 0; i < 26; ++i){
    vector<char> sequencia;
    double qaux = 0.0;
    for(int j = 0; j < fatia.size(); ++j){
      char seq = (((fatia[j]-'A'-i+26) % 26)+'A');
      sequencia.push_back(seq);
    }
    vector<double> contFreq(26,0);
    for(int j = 0; j < sequencia.size(); ++j)
      contFreq[(sequencia[j]-'A')]++;

    for(int j = 0; j < 26; ++j)
      contFreq[j] = (contFreq[j]/fatia.size());

    for(int j = 0; j < 26; ++j){
      double aux1 = (contFreq[j] - (freqIdioma[j]));
      qaux += (aux1*aux1/(freqIdioma[j]));
    }
    X2[i] = qaux;
  }
  aux2 = X2;
  sort(aux2.begin(), aux2.end());
  int indice = 0;
  for(int i = 0; i < X2.size(); ++i){
    if(aux2[0] == X2[i])
      indice = i;
  }
  return (indice + 'A');
}

string quebraChave(int tamanho, int idioma){
  string chave;
  for(int i = 0; i < tamanho; ++i){
    string seq = vSequencia[tamanho][i];
    chave += frequencia(seq, idioma);
    vSequencia[i].clear();
  }
  return chave;
}

int tamChave(string mensagem){
  vector<double> indc, aux;
  int tenta = 0, tenta1 = 0;
  
  for(int i = 1; i <= TAM_MAX_CHAVE; ++i){
    double icMedia = 0.0, icSoma = 0.0;
    for(int j = 0; j < i; ++j){
      string sequencia = "";
      for(int k = 0; k < mensagem.length() - j; k+=i)
        sequencia += mensagem[j+k];
      
      vSequencia[i].push_back(sequencia);
      if(sequencia.length() > 1)
        icSoma += indCoincid(sequencia); 
    }
    if(!i)
      icMedia = icSoma/i;

    indc.push_back(icMedia);
  }
  aux = indc;
  
  sort(aux.begin(), aux.end(), greater<double>());

  for(int i = 0; i < indc.size(); ++i){
    if(aux[0] == indc[i])
      tenta = i+1;

    if(aux[1] == indc[i])
      tenta1 = i+1;
  }
  if(tenta % tenta1)
    return tenta;
  else
    return tenta1;
}

void descChave(string mensagem, int idioma){
  string chave;
  string texto = juntText(mensagem);
  int tam = tamChave(texto);
  
  cout << "Tamanho da chave: " << tam << endl;
  chave = quebraChave(tam, idioma);

  cout << "Chave: " << chave << endl;
  mensagem = decifrador(mensagem, chave);

  cout << "\nmensagem: \n" << mensagem << endl;
}
