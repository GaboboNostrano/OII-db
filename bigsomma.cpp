#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#pragma GCC optimize ("-03")

class FileReader {
	private:
	FileReader(const FileReader&fr){}	
	int maxBufferSize,bufferSize,bufferPointer;int fileNo;char*buffer;
	void loadBuffer(){bufferSize=read(fileNo,buffer,maxBufferSize);bufferPointer=0;}
	inline char nextChar(){if(bufferPointer>=bufferSize)loadBuffer();return buffer[bufferPointer++];}
	bool skipSpaces(){char c;if((c=nextChar())==' ')bufferPointer++;if(c=='\0')return 0;bufferPointer--;return 1;}	
	public:
	FileReader(const char*_name,int _bufferSize=250000){buffer=(char*)malloc(_bufferSize);fileNo=open(_name,O_RDONLY);maxBufferSize=_bufferSize;loadBuffer();}
	FileReader(int _fileNo,int _bufferSize=250000){buffer=(char*)malloc(_bufferSize);fileNo=_fileNo;maxBufferSize=_bufferSize;loadBuffer();}
	~FileReader(){free(buffer);close(fileNo);} 
	int readInt(){return(int)readLongLong();}
	long long readLongLong(){long long n=0;int mul=1;char c;if(!skipSpaces())abort();c=nextChar();if(c=='-')mul=-1;else bufferPointer--;do{c=nextChar();if(c>='0'&&c<='9')n=n*10+(c-'0');}while(c>='0'&&c<='9');return n*mul;}
};

long long somma(FILE *f)
{
    FileReader fr(fileno(f));
    int n = fr.readInt();
    long long somma = 0;
    for(long long i=n;i>0;i--)
    {
        somma += fr.readLongLong();
    }
    return somma;
}