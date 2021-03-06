Yusuf CEYLAN


/*Ödev kapsamında Matrix sınıfı ve bu sınıftan miras alınarak türetilen
Image ve Table sınıfları oluşturulmuştur. Ödev kapsamında operator
ve fonksiyon overloading, template sınıflar kullanılmıştır. Matrix 
sınıfında matris islemleri gerceklestirilmistir. Image sinifi icin 
bir struct yapisi olusturularak goruntu isleme kapsaminda,.bin uzantili
dosyalari okuma,yazma, renkli goruntuyu griye, gri goruntuyu binary 
goruntuye donusturme, morfolojik asindirma, yayma, acma, kapama 
islemleri gerceklestirilmistir. Table sinifi icin satir ve sutunlar
isimlendirilerek matristen tablo olusturma, satir ve sutun isimlerinin
guncellenebilmesi, istenen indisteki degerin dondurulmesi islemleri
yapilmistir. */

#include <iostream>  
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

//Matris sinifi olusturulur
 template<class T> class Matrix
 {
     protected:
             int satir;
             int sutun;
             T **matris;
     public:
             Matrix();
            // virtual ~Matrix();
             Matrix(int, int, T);
             Matrix(int, int, char);
             void print();
             void resize(int, int);
             void print(string);
             Matrix<T> operator+(const Matrix<T> &);
             Matrix<T> operator-(const Matrix<T> &);
             Matrix<T> operator*(const Matrix<T> &);
             Matrix<T> operator+(int);
             Matrix<T> operator-(int);
             Matrix<T> operator*(int);
             Matrix<T> operator/(int);
             Matrix<T> operator%(int);
             Matrix<T> operator^(int);
             T **matrisAl();
             void degerAta(int,int,T);
             Matrix<T> Tranpoze();
             Matrix<T> emul(const Matrix<T> &);
             int Determinant();
             Matrix<T> Inversion(); 
                        
  };
 // 10x10 0 degerli matris constructorı
template<class T> Matrix<T>::Matrix()
{
     satir = 10, sutun= 10;
     matris = new T *[satir];
     for(int i=0; i<satir; i++)
     {
         matris[i] = new T [sutun];
     }
     for(int i=0; i<satir; i++)
     {
         for(int j=0; j<sutun; j++)
         {
             matris[i][j] = 0;
         }
     }
}
//destructor
/*template<class T> Matrix<T>::~Matrix()
{
	for (int i = 0; i < this->sutun; i++)
		delete[] this->matris[i];
	delete[] this->matris;
}
*/

// T degerli, parametreli constructor
template<class T> Matrix<T>::Matrix(int str, int stn, T deger) 
{
     satir = str, sutun= stn;
     matris = new T *[satir];
     for(int i=0; i<satir; i++)
     {
         matris[i] = new T [sutun];
     }
     for(int i=0; i<satir; i++)
     {
         for(int j=0; j<sutun; j++)
         {
             matris[i][j] = deger;
         }
     }
}
 // char degerli, parametreli constructor 
template<class T> Matrix<T>::Matrix(int str, int stn, char deger)
{
     satir = str, sutun= stn;
     matris = new T *[satir];
     for(int i=0; i<satir; i++)
     {
         matris[i] = new T [sutun];
     }
     //Zamana bagli olarak random atanan degerleri degistirir
     srand(time(NULL));  
     
     for(int i=0; i<satir; i++)
     {
         for(int j=0; j<sutun; j++)
         {
            if(deger == 'e') // Birim Matris Olusturma
            {
                if(satir == sutun) //Satir ve sutun esit ise olustur.
                {
                     if(i==j)
                    {
                        matris[i][j] = 1;
                    }
                    else
                    {
                        matris[i][j] = 0;
                    }
                }
                else  //Satir ve sutun esit değilse hata mesaji ver
                {
                    cout<<"Birim Matris İcin Satir-Sutun Esit Olmali";
                    exit(0); // Programdan cik
                }
               
            }
           
            else if (deger == 'r') // random deger atama
            {
                // 0-255 arasinda deger almasi
                matris[i][j] = rand()%256 ; 
            }
           
           
         }
     }
       
}

//matrisi döndür
template<class T> T** Matrix<T>::matrisAl()
{
	return matris;
}

//Verilen satir ve sutun icin deger atama
template<class T> void Matrix<T>::degerAta(int str,int stn,T deger)
{	
    matris[str][stn] = deger;
}

//Matrisi verilen degerlere göre yeniden boyutlandır 
template<class T> void Matrix<T>::resize(int str,int stn)
{ 
	if (this->satir > str)
	{
		for (int i = str; i < this->satir; i++)
		{
			delete [] matris[i];
		}
	}
	else
	{
		this->matris = (T**)realloc(this->matris,str*sizeof(T*));
	}
	
	this->satir = str;

	for (int i = 0; i < this->satir; i++)
	{
			this->matris[i] = (T*)realloc ( matris[i],stn*sizeof(T));
	}
	this->sutun = stn;

}

//Dosyaya yazma 
template<class T> void Matrix<T>::print(string a)
{
    ofstream dosya;
    dosya.open("file.txt");
    for(int i=0; i<satir; i++)
      {
         for(int j=0; j<sutun; j++)
         {
             dosya<<matris[i][j]<<"  ";
         }
         dosya<<endl;
      }
      dosya.close();
}

// Ekrana yazdırma fonksiyonu 
template<class T> void Matrix<T>::print()
{
      for(int i=0; i<satir; i++)
      {
         for(int j=0; j<sutun; j++)
         {
             cout<<matris[i][j]<<"  ";
         }
         cout<<endl;
      }
   
}

//matris operator overloading +
template<class T> Matrix<T> Matrix<T>::operator+(const Matrix<T> &b)
{
    if(b.satir == satir && b.sutun == sutun)
    {
         Matrix<T> gecici(satir,sutun,0);
         for(int i=0; i<satir; i++)
         {
             for(int j=0; j<sutun; j++)
             {
                 gecici.matris[i][j] =  matris[i][j] + b.matris[i][j];
             }
         }
        return gecici;
    }
    exit(0);
}

//matris operator overloading -
template<class T> Matrix<T> Matrix<T>::operator-(const Matrix<T> &b)
{
    if(b.satir == satir && b.sutun == sutun)
    {
         Matrix<T> gecici(satir,sutun,0);
         for(int i=0; i<satir; i++)
         {
             for(int j=0; j<sutun; j++)
             {
                 gecici.matris[i][j] =  matris[i][j] - b.matris[i][j];
             }
         }
        return gecici;
    }
    exit(0);
}

//matris operator overloading 
template<class T> Matrix<T> Matrix<T>::operator*(const Matrix<T> &b)
{	

   if(sutun!=b.satir)
   {
       cout<< "Bu islem yapilamaz" << endl;
       cout << "İlk matrisin sutun sayisi ile "
       		<<" ikinci matrisin satir sayisi esit olmalı" <<endl;
       	exit(0);
   }
   
   else if(sutun == b.satir)
   {
       	Matrix<T> gecici(satir,b.sutun,0);
        for(int i=0; i<satir; i++)
        {
            for(int j=0; j<b.sutun; j++)
            {
                for(int k=0; k<b.satir; k++)
                {
                    gecici.matris[i][j]+=matris[i][k]*b.matris[k][j];
                }
            }
        }
        return gecici;
   }
   exit(0);
}

//skaler operator overloading *
template<class T> Matrix<T> Matrix<T>::operator*(int value)
{
         Matrix<T> gecici(satir,sutun,0);
         for(int i=0; i<satir; i++)
         {
             for(int j=0; j<sutun; j++)
             {
                 gecici.matris[i][j] =  matris[i][j] * value;
             }
         }
        return gecici;
}

//skaler operator overloading +
template<class T> Matrix<T> Matrix<T>::operator+(int value)
{
         Matrix<T> gecici(satir,sutun,0);
         for(int i=0; i<satir; i++)
         {
             for(int j=0; j<sutun; j++)
             {
                 gecici.matris[i][j] =  matris[i][j] + value;
             }
         }
        return gecici;
}
 
//skaler operator overloading -  
template<class T> Matrix<T> Matrix<T>::operator-(int value)
{
         Matrix<T> gecici(satir,sutun,0);
         for(int i=0; i<satir; i++)
         {
             for(int j=0; j<sutun; j++)
             {
                 gecici.matris[i][j] =  matris[i][j] - value;
             }
         }
        return gecici;
}  

//skaler operator overloading /   
template<class T> Matrix<T> Matrix<T>::operator/(int value)  
{	     //double da 1 - 1.0 a dönüsecek
         Matrix<T> gecici(satir,sutun,1.0);
         for(int i=0; i<satir; i++)
         {
             for(int j=0; j<sutun; j++)
             {
                 gecici.matris[i][j] = matris[i][j] / value;
             }
         }
        return gecici;
}  

//skaler operator overloading %     
template<class T> Matrix<T> Matrix<T>::operator%(int value)
{
         Matrix<T> gecici(satir,sutun,0);
         for(int i=0; i<satir; i++)
         {
             for(int j=0; j<sutun; j++)
             {
                 gecici.matris[i][j] =  matris[i][j] % value;
             }
         }
        return gecici;
}  

//skaler operator overloading ^
template<class T> Matrix<T> Matrix<T>::operator^(int value)
{
    if(value>0)
    {
    	//1 degerli matris olusturma
    	//Negatif us alirken 3. parametre 1.0 a donusturulur
        Matrix<T> gecici(satir,sutun,1);
        for(int i=0; i<satir; i++)
        {
            for(int j=0; j<sutun; j++)
            {
                for(int k=0; k<value; k++)
                {
                    gecici.matris[i][j] *= matris[i][j];
                }
            }
        }
        return gecici;
    }
   
    else if(value<0)
    {
    	//deger pozitife cevrilir
        value = (-1)*value;
        //Negatif us alirken 3. parametre 1.0 a donusturulur
        Matrix<T> gecici(satir,sutun,1);
        for(int i=0; i<satir; i++)
        {
            for(int j=0; j<sutun; j++)
            {
                for(int k=0; k<value; k++)
                {
                    gecici.matris[i][j] *= matris[i][j];
                   
                }
                gecici.matris[i][j] = 1.0 / gecici.matris[i][j];
            }
        }
        return gecici;
    }
    else
    {
    	//Negatif us alirken 3. parametre 1.0 a donusturulur
        Matrix<T> gecici(satir,sutun,1);
        return gecici;
    }
}

//Transpozu alır, Matrix nesnesi olarak dondurur
template<class T> Matrix<T> Matrix<T>::Tranpoze()
{
    Matrix<T> gecici(sutun,satir,0);
    for(int i=0; i<sutun; i++)
    {
        for(int j=0; j<satir; j++)
        {
           gecici.matris[i][j] = matris[j][i];
           
           
        }
       
    }
    return gecici;
   
}

//İki matrisi eleman düzeyinde carpar
template<class T> Matrix<T> Matrix<T>::emul(const Matrix<T> &b)  
{
    Matrix<T> gecici(satir,sutun,0);
    if(satir == b.satir && sutun == b.sutun)
    {
        for(int i=0; i<satir; i++)
        {
            for(int j=0; j<sutun; j++)
            {
                gecici.matris[i][j] =  matris[i][j] * b.matris[i][j];
            }
        }
        return gecici;
    }
    exit(0);
}

//Determinant hesaplar
template<class T> int Matrix<T>::Determinant()
{
    if(satir == sutun)
    {
        int det = 0,p,h,k;
        int sign = 1;
        if(satir==1)
        {
        	det=matris[0][0];
        	return det;
        }
          else if(satir==2)
        {
            det=(matris[0][0]*matris[1][1]-matris[0][1]*matris[1][0]);
            return det;
        }
      
        else
        {
        	//Inversion icin 3. parametre 0.0 olarak degismeli 
            Matrix<T> fani(satir-1,sutun-1,0); 
            for(int p=0;p<satir;p++)
            {
                h = 0;
                k = 0;
                for(int i=1;i<satir;i++)
                {
                    for(int j=0;j<satir;j++)
                    {
                        if(j==p)
                        {
                            continue;
                        }
                        fani.matris[h][k] = matris[i][j];
                        k++;
                        if(k==satir-1)
                        {
                        	h++;
                        	k=0;
                        }
                    } 
                }
            //Recursive ile determinant hesaplar    
            det=det+matris[0][p]*sign*fani.Determinant();
            sign *=-1;
            }
    	return det;
        }
    }
    else
    {
        cout<< "Determinant Hesaplamak İcin Kare Matris Olmali!!!";
        exit(0);
    }
}

//Matrisin tersini alir.
template<class T> Matrix<T> Matrix<T>::Inversion()
{
    if(Determinant()!=0.0)
    {
       if(satir==sutun)
       {
            Matrix<T> birim(satir,sutun,'e');//birim matris olusturulur
            float d,k;
            for(int i=0; i<satir; i++)
            {
                float b=matris[i][i];
                for(int j=0; j<satir; j++)
                {
                    matris[i][j] = matris[i][j] / b;
                    birim.matris[i][j] = birim.matris[i][j] / b; 
                }
                for(int x=0; x<satir; x++)
                {
                    if(x!=i)
                    {
                        k=matris[x][i];
                        for(int j=0; j<satir; j++)
                        {
                           matris[x][j]=matris[x][j]-(matris[i][j]*k);
                           birim.matris[x][j]-=(birim.matris[i][j]*k);
                        }
                    }
                }
            
            }
        return birim;
          
        }
        exit(0);
    }
    else
    {
        cout<< "Matrisin Tersi İcin Det. Sifirdan Farkli Olmali!!!";
        exit(0);
    }
}

//Image sinifinda kullanılmak üzere rgb struct ı olusturulur.
struct rgb
{
	int red = 0;
	int green = 0;
	int blue = 0;
};

//Matris sinifindan miras alinarak Image sinifi olusturulur.
class Image : private Matrix <rgb>
{
	public:
		Image();
		Image(int,int);
		void color2gray();
		Image(string,string);
		void imWrite(string, string);
		void imRead(string,string);
		void gray2binary(int);
		void erosion();
		void dilation();
		void opening();
        void closing();
        void printText();
};

//255x255 boyutunda 0 degerli constructor 
Image::Image():Matrix(255,255,rgb())
{
	for(int i=0; i<255; i++)
	{
		for(int j=0; j<255; j++)
		{
			matris[i][j].red = 0;
			matris[i][j].green = 0;
			matris[i][j].blue = 0;
		}
	}
}

//verilen satir ve sutun degerleri ile boyutu belirlenen constructor
Image::Image(int satir, int sutun):Matrix(satir,sutun,rgb())
{
	for(int i=0; i<satir; i++)
	{
		for(int j=0; j<sutun; j++)
		{
			matris[i][j].red = 0;
			matris[i][j].green = 0;
			matris[i][j].blue = 0;
		}
	}
}

//Renkli goruntuyu griye cevirme 
void Image:: color2gray()
{
	for(int i=0; i<satir; i++)
	{
		for (int j = 0; i <sutun; i++)
		{
			matris[i][j].green =(0.299*matris[i][j].red)+
								(0.587*matris[i][j].green)+
								(0.114*matris[i][j].blue);
			matris[i][j].blue = 0;
			matris[i][j].red = 0;
		}
	}
}

//.bin uzantili dosyayi okuyan constructor
Image::Image(string dosyaAdi,string format):Matrix(1,1, rgb())
{	
	char *gecici;
	string dosya = "";
	dosya = dosyaAdi +"."+ format;
    ifstream myFile (dosya, ios::binary);
	int satir_,sutun_;
	gecici= new char[1];
	if (myFile) 
	{
		
		myFile.read(gecici,1);
		//ilk byte satiri tutar 
		satir_= (unsigned int)(unsigned char)(gecici[0]);
		myFile.read(gecici,1);
		//ikinci byte sutunu tutar
		sutun_= (unsigned int)(unsigned char)(gecici[0]);

		
		resize(satir_,sutun_);
		for (int i = 0; i < this->satir; i++)
		{
			for (int j = 0; j < this->sutun; j++)
			{	
				myFile.read(gecici,1);
				matris[i][j].green = 
					(unsigned int)(unsigned char)(gecici[0]);
			}
			
		}
    }
}

//Goruntuyu .bin uzantili dosyaya yazar
void Image::imWrite(string dosyaAdi, string format)
{
	char *gecici;
	string dosya = dosyaAdi +"."+ format;
    ofstream myFile (dosya, ios::binary);

	if (myFile) {

		gecici = new char[1];
		*gecici = (char)(unsigned char)(this->satir);
		myFile.write(gecici,1);

		*gecici = (char)(unsigned char)(this->sutun);		
		myFile.write(gecici,1);

		for (int i = 0; i < this->satir; i++)
		{
			for (int j = 0; j < this->sutun; j++)
			{	
				*gecici = 
					(char)(unsigned char)(this->matris[i][j].green);
				myFile.write(gecici,1);
			}
		}
    }
}

//gri goruntuyu ikili goruntuye cevirir
void Image::gray2binary(int thr)
{
	for (int i = 0; i < this->satir; i++)
	{
		for (int j = 0; j < this->sutun; j++)
		{	
			if (thr > matris[i][j].green)
			{
				this->matris[i][j].green = 0;
			}else
			{
				this->matris[i][j].green = 1;
			}
		}
	}
}

//.bin uzantili dosyayi okuyan fonksiyon
void Image::imRead(string dosyaAdi, string format)
{	
	Image(dosyaAdi,format);
}

//morfolojik asindirma islemi gerceklestirilir
void Image::erosion()
{	
	Matrix<rgb> n(this->satir,this->sutun,rgb());

	for (int i = 0; i < this->satir; i++)
	{
		for (int j = 0; j < this->sutun; j++)
		{
			n.degerAta(i,j,(this->matris[i][j]));
		}
	}
	
	for (int i = 0; i < satir; i++)
	{
		for (int j = 0; j < sutun; j++)
		{	
			if (n.matrisAl()[i][j].green==1)
			{	
				for (int k = -1; k< 2; k++)
				{
					for (int l = -1; l < 2; l++)
					{	
						if ((i+k > 0)
							 && (j+l>0)
							 &&	(i+k < satir)
							 && (j+l < sutun)
							 && (n.matrisAl()[i+k][j+l].green == 0))
						{	
							this->matris[i][j].green = 0;
							k = 3;
							l = 3;
						}
						
					}		
				}
			}
		}
	}
}

//morfolojik yayma islemi gerceklestirilir
void Image::dilation()
{	
	Matrix<rgb> n(this->satir,this->sutun,rgb());

	for (int i = 0; i < this->satir; i++)
	{
		for (int j = 0; j < this->sutun; j++)
		{
			n.degerAta(i,j,(this->matris[i][j]));
		}
		
	}
	
	for (int i = 0; i < satir; i++)
	{
		for (int j = 0; j < sutun; j++)
		{	
			if (n.matrisAl()[i][j].green==0)
			{	
				for (int k = -1; k < 2; k++)
				{
					for (int l = -1; l < 2; l++)
					{	
						if ((i+k > 0)
							 && (j+l>0)
							 &&	(i+k < satir)
							 && (j+l < sutun)
							 && (n.matrisAl()[i+k][j+l].green == 1))
						{	
							this->matris[i][j].green = 1;
							k = 3;
							l = 3;
						}
						
					}		
				}
			}
		}
	}
}

//Morfolojik acma islemi fonksiyonlar cagirilarak gerceklestirilir
void Image::opening()
{
	this->erosion();
	this->dilation();
}

//Morfolojik kapama islemi fonksiyonlar cagirilarak gerceklestirilir
void Image::closing()
{
	this->dilation();
	this->erosion();
}

void Image::printText()
{	
	cout<<"\n\n";
	for(int i=0;i<satir;i++)
	{
		for(int j=0;j<sutun;j++)
		{
			cout<<matris[i][j].green<<""<<flush;
		}
		cout<<endl;
	}
}

//Matris sinifindan miras alinarak Table sinifi olusturulur.
template<class X> class Table : private Matrix<int>
{
	protected:
		string *sutunAdi = NULL;

		string *satirAdi = NULL;
		void sutunAdiOlustur();
		void satirAdiOlustur();

	public:
		Table();
		Table(int, int, int);
		Table(int, int, char);
		X iteamAt(int,int);
		X iteamAt(string,string);
		X iteamAt(string);
		void print();
		void satirAdiDuzenle(string s[], int);
		void sutunAdiDuzenle(string s[], int);


};

//Tablodaki sutunlar sayisina gore sutun isimlerini olusturur
template<class X> void Table<X>:: sutunAdiOlustur()
{
	sutunAdi = new string[sutun];

	for(int i=0; i<sutun; i++)
	{
		sutunAdi[i] = string(1, i+65);

		if((i+65) == 90)
		{
			break;
		}
	}
}

//Tablodaki satir sayisina gore satir isimlerini olusturur
template<class X> void Table<X>:: satirAdiOlustur()
{
	satirAdi = new string[satir];

	for(int i=0; i<satir; i++)
	{
		satirAdi[i] = to_string(i);
	}
}

//Parametresiz constructor
template<class X> Table<X>::Table():Matrix()// 10x10 0 degerli tablo 
{
	this->sutunAdiOlustur();
	this->satirAdiOlustur();
}

//int degerli, parametreli constructor
template<class X>Table<X>::Table(int satir,int sutun,int deger)
	:Matrix(satir,sutun,deger)
{
	this->sutunAdiOlustur();
	this->satirAdiOlustur();
}
 
 //char degerli, parametreli constructor  
template<class X> Table<X>::Table(int satir,int sutun,char deger)
	:Matrix(satir, sutun, deger)
{	
	this->sutunAdiOlustur();
	this->satirAdiOlustur();
}

//verilen satir ve sutundaki degeri dondurur
template<class X> X Table<X>::iteamAt(int satir_,int sutun_)
{
	return matris[satir_][sutun_];
} 

//verilen satir ve sutundaki degeri dondurur/ornek("1","A")
template<class X> X Table<X>::iteamAt(string str_, string stn_)
{
	for(int i=0; i<this->satir; i++)
	{
		for(int j=0; j<this->sutun; j++)
		{
			if((str_.compare(satirAdi[i]) == 0) 
				&& (stn_.compare(sutunAdi[j]) == 0))
			{
				return this->matris[i][j];
			}
		}
	}
	return -1;
}

//verilen satir ve sutundaki degeri dondurur/ornek:("A2")
template<class X> X Table<X>::iteamAt(string c)
{
	for(int i=0; i<this->satir; i++)
	{
		for(int j=0; j<this->sutun; j++)
		{
			if(c[0] == sutunAdi[j][0] && c[1] == satirAdi[i][0])
			{
				return this->matris[i][j];
			}
		}
	}
	return -1;	
} 

//Girilen parameteye gore satir isimlerini gunceller
template<class X> void Table<X>::satirAdiDuzenle(string s[], int b)
{
	for(int i=0; i<b; i++)
	{	
		if (s[i].length()>8)
		{
			string gecici = s[i].substr(0,8);
			satirAdi[i] = gecici;
		}
		else
		{
			satirAdi[i] = s[i];

		}
	}	
}

//Girilen parameteye gore sutun isimlerini gunceller
template<class X> void Table<X>::sutunAdiDuzenle(string s[], int b)
{
	for(int i=0; i<b; i++)
	{
		if(s[i].length()>4)
		{
			string gecici = s[i].substr(0,4);
			sutunAdi[i] = gecici;
		}
		else
		{
		sutunAdi[i] = s[i];
		}
	}	
}

//Tabloyu ekrana yazdirir
template<class X> void Table<X>::print()
{	
	cout<<"\t";
	for (int i = 0; i < this->sutun; i++)
	{
		cout<<setw(8)<<sutunAdi[i];
	}

	cout<<"\n";
	
	for (int i = 0; i < this->satir; i++)
	{	
		cout<<setw(8)<<satirAdi[i];
		for (int j = 0; j < this->sutun; j++)
		{	
			
			cout<<setw(8)<<this->matris[i][j];
		}
		cout<<"\n";
	}
}





int main()
{
	//MATRİX
 //Matrix<int> *m1 = new Matrix<int>();
 //m1->print();
 //Matrix<int> *m2 = new Matrix<int>(5,5,4);
 //m2->print();
// Matrix<int> *m3 = new Matrix<int>(4,4,3);
 //m3->print();
 //Matrix<double> *m4 = new Matrix<double>(5,5,5.0);
 //Matrix<int> *m4 = new Matrix<int>(5,5,'r');
// m2->print();
// m3->print();
 //m4->print("file.txt");
//Matrix<int> m55(2,2,3);
//Matrix<int> m66(2,3,10);
//Matrix<int> mtemp;
//mtemp = m55*m66;
//mtemp.print();
// (*m2) = (*m2) + (*m3);
 //(*m4) = (*m4) ^ (-2);
 //m4->print();
 // (*m2) = (*m2) % 4;
 // m2->print();
 // m2->resize(10,10);
 //m2->print();
  // (m4->Tranpoze()).print();
   // (m2->Tranpoze()).print();
   // m2->print();
  //(m2->emul(*m3)).print();
 //int a = m2->Determinant();
 //  cout << a;
  // (m2->Inversion()).print();

	//IMAGE
	/*
	Image img2(180,180);
	


	Image img3("custom","bin");
	img3.imWrite("deneme1","bin");
	img3.gray2binary(15);
	img3.printBinaryImage();
	cout<<endl<<" custom bin erosion "<<endl;
	img3.erosion();

	Image img4("custom","bin");
	cout<<endl<<" custom bin dilation "<<endl;
	img4.dilation();

	Image img5("custom","bin");
	cout<<endl<<" custom bin closing "<<endl;
	img5.closing();

	Image img6("custom","bin");
	cout<<endl<<" custom bin opening "<<endl;
	img6.opening();
	*/
	/*
	Image img2(200,200);
	Image img3("custom","bin");
	Image img4("custom","bin");
	Image img5("custom","bin");
	Image img6("custom","bin");
	img3.imWrite("sasa","bin");
	cout<<"gray image"<<endl;
	img3.printText();
	img3.gray2binary(15);
	img4.gray2binary(15);
	img5.gray2binary(15);
	img6.gray2binary(15);
	cout<<"custom bin"<<endl;
	img3.printText();
	cout<<endl<<" custom bin erosion "<<endl;
	img3.erosion();
	img3.printText();
	cout<<endl<<" custom bin dilation "<<endl;
	img4.dilation();
	img4.printText();

	cout<<endl<<" custom bin closing "<<endl;
	img5.closing();
	img5.printText();

	cout<<endl<<" custom bin opening "<<endl;
	img6.opening();
	img6.printText();
	*/


  // 	Image img;
 //  	img.color2gray();   
 //  	Table<int> tablo();
 //Image img;
 //img.imWrite("aaaaa","bin");

 //cout<<endl<<ccc.iteamAt("A1")<<endl;
// Image ddd("image2","bin");
 //ddd.gray2binary(100);

   //TABLE
	//(Table<int>()).print();
	//(Table<int>(10,15,3)).print();
	//(Table<int>(10,15,'r')).print();
	/*Table<int> t1(10,10,'r');
	cout<<t1.iteamAt(2,8);
	t1.print();
	*/
	/*Table<int> t1(10,10,'r');
	cout<<t1.iteamAt("A2");
	t1.print();
	*/
	/*
	Table<int> t1(10,10,'r');
	cout<<t1.iteamAt("1","A");
	t1.print();
	*/
	/*
	string s[] = {"0.satir","1.satir"};
	Table<int> t1(10,10,'r');
	t1.satirAdiDuzenle(s,2);
	t1.print();
	*/
	/*
	Table<int> *tb= new Table<int>(15,15,'r');
	string s[] = {"0.satir","1.satir"};
	tb->satirAdiDuzenle(s,2);
	tb->print();
	*/
	/*
	Table<int> *tb= new Table<int>(15,15,'r');
	string s[] = {"0.satir","1.satir"};
	tb->satirAdiDuzenle(s,2);
	tb->print();
	cout << tb->iteamAt("1.satir","B");
	*/
	/*
	string s[] = {"0.satirrrr","1.satirrrrr"};
	Table<int> t1(10,10,'r');
	t1.sutunAdiDuzenle(s,2);
	t1.print();
	*/
	/*
	Table<int> *tb= new Table<int>(15,15,'r');
	string s[] = {"0.satir","1.satir"};
	tb->satirAdiDuzenle(s,2);
	tb->print();
	*/
	/*
	Table<int> *tb= new Table<int>(15,15,'r');
	string s[] = {"0.satir","1.satir"};
	tb->satirAdiDuzenle(s,2);
	tb->print();
	cout << tb->iteamAt("1.satir","B");
	*/
 	//Table<int> ccc(5000,8,'r');
 	//ccc.print();

	return 0;

}
