#include <iostream>
#include <string>
#include <random>
#include <array>
#include <math.h>
#include <vector>

using namespace std;

class Bucket {
    public:
    vector<unsigned long> record;
    vector<unsigned long> overflow_bucket;
    int record_count=0;
    static int bucket_count;
    Bucket() {
        bucket_count++;
    }
    void push_element(unsigned long data) {
        record.push_back(data);
        record_count++;
    }
};

int Bucket::bucket_count=0;
vector<unsigned long> temp;
vector<Bucket> bucket;
int split_index=0;
int level=0;
int d=1;
int N=0;

unsigned long generate_random_number() {
    unsigned long x;
    cout <<"Enter the element: ";
    cin >> x;
    return x;
}

int hash_function(unsigned int data, int d) {
    int index=data%d;
    return index;
}

void display(){
    for(vector<Bucket>::iterator it=bucket.begin();it!=bucket.end();++it) {
        if(it->record.empty()==true) {
            cout <<"Bucket is empty"<<endl;
            continue;
        }
        for(vector<unsigned long>::iterator itr=it->record.begin();itr!=it->record.end();++itr) {
            cout << *itr <<" ";
        }
        if(it->overflow_bucket.empty()==false)
            for(vector<unsigned long>::iterator itr=it->overflow_bucket.begin();itr!=it->overflow_bucket.end();++itr) {
                cout << *itr <<" ";
            }
        cout << endl;
    }
}

void reinsert(unsigned long data) {
    int index=hash_function(data,d);
    if(bucket[index].record.size()<4)
        bucket[index].push_element(data);
    else bucket[index].overflow_bucket.push_back(data);
}

void rehash() {
    vector<Bucket>::iterator it=bucket.begin()+split_index;
    split_index++;
    if(d==N) {
        level++;
        split_index=0;
    }
    if(it->record.empty()==false) {
        for(vector<unsigned long>::iterator itr=it->record.begin();itr!=it->record.end();++itr)
            temp.push_back(*itr);
        it->record.clear();
        it->record_count=0;
    }
    if(it->overflow_bucket.empty()==false) {
        for(vector<unsigned long>::iterator itr=it->overflow_bucket.begin();itr!=it->overflow_bucket.end();++itr)
            temp.push_back(*itr);
        it->overflow_bucket.clear();
    }
    if(temp.empty()==false)
        for(vector<unsigned long>::iterator itr=temp.begin();itr!=temp.end();++itr) {
            reinsert(*itr);
        }
    temp.clear();
}

void insert_data() {
        unsigned long data=generate_random_number();
        if(level==0) {
            int index=hash_function(data,d);
                if(bucket[index].record.size()<4)
                    bucket[index].push_element(data);
                else {
                    bucket[index].overflow_bucket.push_back(data);
                    Bucket b1;
                    bucket.push_back(b1);
                    N=b1.bucket_count;
                    d=ceil(log2(N));
                    d=pow(2,d);
                    rehash();
                }
        }

        else {
            if(N==2) {
                int index=hash_function(data,d);
                if(bucket[index].record.size()<4)
                    bucket[index].push_element(data);
                else {
                    bucket[index].overflow_bucket.push_back(data);
                    Bucket b1;
                    N=b1.bucket_count;
                    d=ceil(log2(N));
                    d=pow(2,d);
                    bucket.push_back(b1);
                    rehash();
                }
            }
            else {
                int index=hash_function(data,d/2);
                if(index<split_index) {
                    int index=hash_function(data,d);
                if(bucket[index].record.size()!=4)
                    bucket[index].push_element(data);
                else {
                    bucket[index].overflow_bucket.push_back(data);
                    Bucket b1;
                    N=b1.bucket_count;
                     d=ceil(log2(N));
                    d=pow(2,d);
                    bucket.push_back(b1);
                    rehash();
                }
                }
                else {
                if(bucket[index].record.size()!=4)
                    bucket[index].push_element(data);
                else {
                    bucket[index].overflow_bucket.push_back(data);
                    Bucket b1;
                    N=b1.bucket_count;
                     d=ceil(log2(N));
                    d=pow(2,d);
                    bucket.push_back(b1);
                    rehash();
                }
            }
        }
    }
}

void search_element(unsigned long data) {
    int b=1,p;
    for(vector<Bucket>::iterator it=bucket.begin();it!=bucket.end();++it,++b) {
        p=1;
        if(it->record.empty()==true)
            continue;
        for(vector<unsigned long>::iterator itr=it->record.begin();itr!=it->record.end();++itr,++p) {
            if(*itr==data) {
                cout << "Element found in bucket " << b << " at position " << p <<endl;
                return;
            }
        }
        p=1;
        if(it->overflow_bucket.empty()==false)
            for(vector<unsigned long>::iterator itr=it->overflow_bucket.begin();itr!=it->overflow_bucket.end();++itr) {
                if(*itr==data) {
                    cout << "Element found in bucket " << b << " at position " << p << " in the overflow" << endl;
                    return;
                }
            }
    }

    cout << "Element not present in hash directory!!!" <<endl;

}

void empty_spaces(int index) {
    int spaces= 4-bucket.at(index-1).record_count;
    if(spaces>0)
        cout <<"There are " << spaces << " spaces left in bucket " << index << endl;
    else
        cout << "Bucket " << index << " is full" << endl;
}

int main() {
    Bucket b;
    N=b.bucket_count;
    bucket.push_back(b);
    int ch,b_no;
    unsigned long data;
    cout << endl;
    cout <<"1. Insert Elements\n"
         <<"2. Display Elements\n"
         <<"3. Search for an element\n"
         <<"4. Display no of bucket splits\n"
         <<"5. Display no of buckets in hash file system\n"
         <<"6. Find empty spaces in a bucket\n"
         <<"7. Current bucket index to split\n"
         <<"8. Exit" << endl;

    while(1) {
        cout <<"Enter choice: ";
        cin>>ch;
        switch(ch) {
            case 1: insert_data();break;
            case 2: display(); break;
            case 3: cout <<"Enter the element to be searched: "; cin >> data;
                    search_element(data); break;
            case 4: cout <<"No of bucket splits are "<<level <<endl; break;
            case 5: cout <<"No of buckets are "<<b.bucket_count <<endl; break;
            case 6: cout <<"Enter bucket number: "; cin >> b_no;
                    empty_spaces(b_no); break;
            case 7: cout <<"Current bucket index to split is "<< split_index <<endl; break;
            case 8: return 0;
            default: cout << "Enter correct choice: "<<endl;
        }
    }
}
