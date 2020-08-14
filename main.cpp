#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>  
#include <queue>
#include <map>

using namespace std;
map<string ,int > m;
priority_queue<pair< int ,string > >pq;

class Book{
	int ISBN, YearOfPublishing, EditionNumbre;
	string BookName, AutherName, PublisherName;
	public :
		//constructor
		Book(int i=0, string b="", string a="", string p="", int y=0, int e=0){
			ISBN=i;
			BookName=b;
			AutherName=a;
			PublisherName=p;
			YearOfPublishing=y;
			EditionNumbre=e;
		}
		int getISBN(){
			return ISBN;
		}
		void setISBN(int i){
			ISBN=i;
		}
		
		string getBookName(){
			return BookName;
		}
		void setBookName(string b){
			BookName=b;
		}
		
		string getAutherName(){
			return AutherName;
		}
		void setAutherName(string a){
			AutherName=a;
		}
		
		string getPublisherName(){
			return PublisherName;
		}
		void setPublisherName(string p){
			PublisherName=p;
		}
		
		int getYearOfPublishing(){
			return YearOfPublishing;
		}
		void setYearOfPublishing(int y){
			YearOfPublishing=y;
		}
		
		int getEditionNumbre(){
			return EditionNumbre;
		}
		void setEditionNumbre(int e){
			EditionNumbre=e;
		}
		
		friend ostream & operator<< (ostream & out ,Book & b){
			out<<b.getISBN()<<", "<<b.getBookName()<<", "<<b.getAutherName()<<", "<<b.getPublisherName()<<", "<<b.getYearOfPublishing()<<", "<<b.getEditionNumbre()<<endl;
			return out;
		}
		friend istream & operator>> (istream & in ,Book & b){
			in>>b.ISBN>>b.BookName>>b.AutherName>>b.PublisherName>>b.YearOfPublishing>>b.EditionNumbre;
			return in;
		}
		friend fstream & operator<< (fstream & file ,Book & b){
			file<<b.getISBN()<<"|"<<b.getBookName()<<"|"<<b.getAutherName()<<"|"<<b.getPublisherName()<<"|"<<b.getYearOfPublishing()<<"|"<<b.getEditionNumbre()<<"\n";
			return file;
		}		
};
fstream file;
Book book;
Book data[300];
Book d[2];
int count=0;
int y=0;
void convertStringToBook(const string record){
	stringstream strs(record);
	string s_ISBN, s_BookName, s_AutherName, s_PublisherName, s_YearOfPublishing, s_EditionNumbre;
	getline(strs,s_ISBN,'|');	
	getline(strs,s_BookName,'|');
	getline(strs,s_AutherName,'|');
	getline(strs,s_PublisherName,'|');
	getline(strs,s_YearOfPublishing,'|');
	getline(strs,s_EditionNumbre,'\n');
	
	book.setISBN(atoi(s_ISBN.c_str()));
	book.setBookName(s_BookName);
	book.setAutherName(s_AutherName);
	book.setPublisherName(s_PublisherName);
	book.setYearOfPublishing(atoi(s_YearOfPublishing.c_str()));
	book.setEditionNumbre(atoi(s_EditionNumbre.c_str()));
}
void arr(){
	file.open("Data.txt",ios::in);
	if(!file){
		cout<<"Cannot open the file in app mode.";
		exit(1);
	}
	string record;
	while(true){
		file>>record;
		if(file.eof()){
			break;
		}
		convertStringToBook(record);
		data[count].setISBN(book.getISBN());
		data[count].setBookName(book.getBookName());
		data[count].setAutherName(book.getAutherName());
		data[count].setPublisherName(book.getPublisherName());
		data[count].setYearOfPublishing(book.getYearOfPublishing());
		data[count].setEditionNumbre(book.getEditionNumbre());
		count++;
		
	}
	file.close();
}
void save(){
	file.open("Data.txt",ios::out);
    if(!file){
	    cout<<"Cannot open the file in app mode.";
	    exit(1);
    }
    for(int i=0;i<count;i++){
    	file<<data[i];
	}
	file.close();
}
void AddBook(){
	int x;
	cout<<"\nEnter the new book details: ";
	cin>>data[count];
	count++;
}
void deleteBook(){
	int dkey;
	cout<<"\nEnter ISBN of book you will delete : ";
	cin>>dkey;
	int i=0;	
	for(;i<count;i++){
		if(data[i].getISBN()==dkey){
			cout<<"\nBook : "<<data[i]<<endl;
			d[0]=data[i];
			break;
		}
	}
	if(i==count){
		cout<<"\nBook not found."<<endl;
		return;
	}
	for(int j=i;j<count;j++){
		data[j]=data[j+1];
	}
	count--;
}

void updateBook(){
	int key;
	cout<<"\nEnter ISBN of book you will update : ";
	cin>>key;
	int i=0;	
	for(;i<count;i++){
		if(data[i].getISBN()==key){
			cout<<"\nBook : "<<data[i]<<endl;
    		cout<<"Enter new Book detials: ";
			cin>>data[i];
			break;
		}
	}
	if(i>=count){
		cout<<"\nBook not found."<<endl;
		return;
	}
}
void findBookISBNLinear(){
	int keyISBN;
	cout<<"\nEnter book ISBN : ";
	cin>>keyISBN;
	for(int i=0;i<count;i++){
		if(data[i].getISBN()==keyISBN){
			cout<<"\nBook found.";
			cout<<"\n"<<data[i];
			string s=data[i].getBookName();
			m[s]++;
			pq.push({m[s],s}); 
			return;
		}
	}
    cout<<"Book not found.\n";
    return;	
}
void findBookISBNBinary(){
	int in,out;
	for(out=count-1;out>1;out--){
		for(in=0;in<out;in++){
			if(data[in].getISBN()>data[in+1].getISBN())
			{
				Book temp=data[in];
				data[in]=data[in+1];
				data[in+1]=temp;
			}
		string s=data[in].getBookName();
		m[s]++;
		pq.push({m[s],s}); 
		}
	}
	int keyISBN;
	cout<<"\nEnter book ISBN : ";
	cin>>keyISBN;

	int l=0,u=count-1;
	int mid;
	while(true){
		mid=(l+u)/2;
		if(data[mid].getISBN()==keyISBN){
			cout<<"\nBook found.";
			cout<<"\n"<<data[mid];
			break;
		}
		else if(l>u){
			cout<<"\nNot found.";
			break;
		} 
		if(data[mid].getISBN()<keyISBN){
			l=mid+1;
		}
		else
			u=mid-1;
		
	}	
}
void displayBooks(){
	for(int x=0;x<count;x++){
		cout<<data[x];
	}
}
void displaySort(){
	int in,out;
	for(out=count-1;out>1;out--){
		for(in=0;in<out;in++){
			if(data[in].getYearOfPublishing()>data[in+1].getYearOfPublishing())
			{
				Book temp=data[in];
				data[in]=data[in+1];
				data[in+1]=temp;
			}
		}
	}
	for(int x=0;x<count;x++){
		cout<<data[x];
	}
}
void displayTheMostPopularBooks(){
	int t=5;
		while( !pq.empty() && t--){ 
            pair<int, string > top = pq.top(); 
            cout << top.second << "\n";
            pq.pop();
		}
        cout<<endl;
}
void undolastdeleteoperation(){
	if(d[0].getISBN()==0){
		cout<<"\nYou did not use delete operation.";
	}
	int z=d[0].getISBN();
	data[count++]=d[0];
	int w;
	cout<<"\nIf you redo last undo enter 1 if you not enter 0: ";
	cin>>w;
	if(w==1){
		int i=0;
		for(;i<count;i++){
	    	if(data[i].getISBN()==z){
		    	break;
		    }
	    }
	    for(int j=i;j<count;j++){
		    data[j]=data[j+1];
		    return;
    	}
    	count--;
    }
	else if(w==0){
		cout<<"\nBook is add.";	
	}
	else{
		cout<<"\nInvalid input.";
	}
}
int main(){
	arr();
	cout<<"The application updates books file";
	cout<<"\n1. When exiting the application";
	cout<<"\n2. When selecting �Save to file� option from your application option menu.";
	cout<<"\n3. When your application has been recorded at least five changes in your Books";
	cout<<"\n-------------------------------------------------------------------------------------------------";
	int choice;
	while (true){
		cout<<"\nEnter 1 to add New Book";
		cout<<"\nEnter 2 to delete Book";
		cout<<"\nEnter 3 to Update Book";
		cout<<"\nEnter 4 to find Book";
		cout<<"\nEnter 5 to Save to file";
		cout<<"\nEnter 6 to display all Book";
		cout<<"\nEnter 7 to undo last delete operation";
		cout<<"\nEnter 8 to display the most 5 popular Books";
		cout<<"\nEnter 9 to quit ";
		cout<<"\n\nEnter your choice ";
		cin>>choice;
		switch(choice){				
			case 1:
				AddBook();
				y++;
				if(y==5){
				   save();
				   y=0;	
				}
				break;
			case 2:
				deleteBook();
				y++;
				break;
			case 3:
				updateBook();
				y++;
				break;
			case 4:
	            cout<<"\nEnter 0 to find Book by ISBN by linear "; 
				cout<<"\nEnter 1 to find Book by ISBN by binary ";
	            int ch;
                cout<<"\n \nEnter your choice ";
		        cin>>ch;
		        if (ch==0){
		        	findBookISBNLinear();
				}
				else if(ch==1){
					findBookISBNBinary();
				}
				else
				cout<<"invalid input.\n";
				break;
			case 5:
				save();
				y=0;
				break;
			case 6:
				cout<<"\nEnter 0 to display books";
	            cout<<"\nEnter 1 to display books sorted asc based on YearOfPublishing";
	            int ch1;
                cout<<"\n \nEnter your choice ";
		        cin>>ch1;
		        if(ch1==0){
		        	displayBooks();
				}
				else if(ch1==1){
					displaySort();
				}
				else
				cout<<"invalid input.\n";
				break;
			case 7:
				undolastdeleteoperation();
				break;
			case 8:
				displayTheMostPopularBooks();
				break;		
			case 9 :
				save();
				y=0;
				break;
			default:
				cout<<"\nInvalid input"<<endl;
				break;		
		}
    }
}
