#ifndef RECORDS_H_INCLUDED
#define RECORDS_H_INCLUDED

class RecordsPuntos{
 char nombre[20];
 int puntos;

public:
    RecordsPuntos(){
        setNombre("");
        setPuntos(0);
    }


    const char * getNombre(){return nombre;}
    int getPuntos(){return puntos;}

    void setPuntos(int p){puntos=p;}
    void setNombre(const char *nom){strcpy(nombre,nom);}


    int leerDeDisco(int pos){
        FILE *p;
        p=fopen("RecordsPuntos.dat", "rb");
        if(p==NULL) return -1;
        fseek(p, sizeof *this*pos,0);
        int leyo=fread(this, sizeof *this,1, p);
        fclose(p);
        return leyo;
    }

    int grabarEnDisco(){
        FILE *p;
        p=fopen("RecordsPuntos.dat", "ab");
        if(p==NULL) return -1;
        int grabo=fwrite(this, sizeof *this,1, p);
        fclose(p);
        return grabo;
    }

    int modificarEnDisco(int pos){
        FILE *p;
        p=fopen("RecordsPuntos.dat","rb+");
        if(p==NULL){return -1;}
        fseek(p, pos*sizeof *this,0);
        int grabo=fwrite(this, sizeof *this,1, p);
        fclose(p);
        return grabo;
    }


};


bool bkpRecordsPuntos(){
    FILE *p;
    p=fopen("RecordsPuntos.bkp", "wb");
    if(p==NULL) return false;

    RecordsPuntos reg;
    int pos=0;
    while(reg.leerDeDisco(pos)==1){
        fwrite(&reg, sizeof reg, 1, p);
        pos++;
    }
    fclose(p);
    if(pos==0)return false;
    return true;
}


#endif // RECORDS_H_INCLUDED
