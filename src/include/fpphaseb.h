#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <stack>
#include <map>

//#include <preprocessing.h> Ԥ����ͷ�ļ�
using namespace std;
int GLB_SUP=10000;
int GLB_CONF=10000;

typedef struct FP_Node
{
    int ip_id;
    struct FP_Node *l_child;//����
    struct FP_Node *r_child;//�ֵ�
    struct FP_Node *father;//���׽ڵ�
    struct FP_Node *pre_item;
    int support;
    FP_Node()
    {
        this->l_child=this->r_child=this->father=this->pre_item=NULL;
    }
}FP_TREE;
typedef struct Flist
{
    int support;
    FP_Node * head;

}F_LIST;
map<int, Flist>Flist_glb;

inline FP_Node* insert_link(FP_Node* p,vector<int> &log_vec,map<int, Flist> &Flist, int sup)
{
    FP_Node *cur;//��ǰ�ڵ�
    int cur_ip;
    for(int j=0;j<log_vec.size();j++)
    {
        cur = p->l_child;
        cur_ip = log_vec[j];
        if(!p->l_child)//����ӿգ��½��ڵ�
        {
            if(!(p->l_child=(FP_Node *)malloc(sizeof(FP_Node))))
            {
                cout<<"lson stack error!!!"<<endl;
                return false;
            };
            cur=p->l_child;
            cur->father=p;
            cur->l_child=cur->r_child=NULL;
            cur->ip_id=cur_ip;
            cur->support=sup;
            //ͷ�巨������index
            cur->pre_item=Flist[cur_ip].head;
            Flist[cur_ip].head=cur;
            p=cur;
        }
        else if(cur->ip_id==cur_ip)//�ж��Ƿ����ڴ˽ڵ�
        {
            cur->support+=sup;
            p=cur;
        }
        else//�������ֵ�
        {
            p=cur;
            while((cur=cur->r_child))//�ֵܽڵ�
            {
                if(cur->ip_id==cur_ip)
                {
                    cur->support+=sup;
                    p=cur;
                    break;
                }
                p=cur;
            }
            if(!cur)//�սڵ�
            {
                if(!(p->r_child=(FP_Node *)malloc(sizeof(FP_Node))))//�½����ֵ�
                {
                    cout<<"rson stack error!!!"<<endl;
                    return false;
                };
                cur=p->r_child;
                cur->father=p->father;//���ڵ�ָ���ֵܽڵ�ĸ��ڵ�
                cur->l_child=cur->r_child=NULL;
                cur->ip_id=cur_ip;
                cur->support=sup;
                 //ͷ�巨������index
                cur->pre_item=Flist[cur_ip].head;
                Flist[cur_ip].head=cur;

                p=cur;
            }
        }
    }
}

void FP_free(FP_Node * root)//�ͷ�fp���ڴ�
{
    if(root->l_child!=NULL)
        FP_free(root->l_child);
    if(root->r_child!=NULL)
        FP_free(root->r_child);
    free(root);
}

void fp_print(FP_Node *cur)
{
    if(!cur)
        return;
    cout<<cur->ip_id<<":"<<cur->support<<",child ={";
    FP_Node *son =cur->l_child;
    while(son)
    {
        cout<<son->ip_id<<":"<<son->support<<",";
        son=son->r_child;
    }
    cout<<"}"<<endl;
    fp_print(cur->l_child);
    fp_print(cur->r_child);
}
void flist_print(map<int, Flist> F)
{
    map<int,Flist>::iterator it;
    for(it=F.begin();it!=F.end();it++)
    {
        FP_Node *cur=(*it).second.head;
        while(cur)
        {
            cout<<cur->ip_id<<":"<<cur->support<<" -> ";
            cur=cur->pre_item;
        }
        cout<<endl;
    }
}
bool build_tree(FP_Node *root,vector<vector<int> > log_frquence)
{
    FP_Node *p;//��ǰ�ڵ�ĸ��ڵ�
    FP_Node *cur;//��ǰ�ڵ�
    int cur_ip;

    for(int i=0;i<log_frquence.size();i++)
    {
        p=root;
        vector<int> log_vec=log_frquence[i];
        insert_link(p,log_vec,Flist_glb,1);//��ʼ��ÿ����Ʒ֧�ֶȼ���Ϊ1
    }
    return true;
}

int FP_growth(FP_Node * root, map<int,Flist> &head_table, vector<int>&alpha)
{
    bool signal_link=true;
    FP_Node *cur = root;
    while(cur->l_child!=NULL)//�ж��Ƿ�Ϊ����·��
    {
        cur=cur->l_child;
        if(cur->r_child!=NULL)
        {
            signal_link = false;//���ǵ���
            break;
        }
    }
    if(signal_link)
    {
        return -1;//����Ƶ���
    }
    else
    {

        map<int,Flist>::iterator it;
        for(it=head_table.begin();it!=head_table.end();++it)
        {
            FP_Node *index=(*it).second.head;
            /*
             *�ڴ����� beta = i U alpha
             ...
             */

            vector<int> beta(alpha);
            beta.push_back(index->ip_id);

            // beta.push_back(ip_id);
            /*
             *����ڵ�i������FP��,FP_Node ,Flist
             */

            FP_Node *cond_fp=(FP_Node *)malloc(sizeof(FP_Node));
            if(cond_fp==NULL)
            {
                cout<<"cond_fp malloc error"<<endl;
                return -1;
            }
            cond_fp->l_child=cond_fp->r_child=NULL;

            vector <int> cond_log;//����FP��������ģʽ��
            map<int, Flist>cond_Flist;//����FP����Flist
            cond_Flist.clear();


            FP_Node *par;//��ʾ����ģʽ����·���ϵĽڵ�

            for(;index!=NULL;index=index->pre_item)
            {
               stack<FP_Node*> cond_pattern;//index������ģʽ����

              par=index;
               while(par=par->father)
               {
                   cond_pattern.push(par);
               }
               cond_log.clear();
               cond_pattern.pop();//ȥ��NULL�ڵ�
               while(!cond_pattern.empty())
               {
                   par=cond_pattern.top();
//                   cout<<par->ip_id<<endl;
                   cond_log.push_back(par->ip_id);
                   cond_pattern.pop();
               }
               /*
                *if(index->support>GLB_SUP)
                */

               insert_link(cond_fp,cond_log,cond_Flist,index->support);//��ʼ��ÿ����Ʒ֧�ֶȼ���Ϊ1
            }
            if(cond_fp->l_child!=NULL)
            {
                FP_growth(cond_fp,cond_Flist,beta);
                cout<<"=--==cond_fp===="<<(*it).second.head->ip_id<<endl;
                fp_print(cond_fp->l_child);
                cout<<"===cond_Flist==="<<endl;
                flist_print(cond_Flist);

                cout<<"beta \n";
                vector<int> ::iterator vi;
                for(vi=beta.begin();vi!=beta.end();vi++)
                {
                    cout<<" "<<(*vi);
                }
                cout<<endl;
            }
            free(cond_fp);
        }
    }
}

//int main()
int testfptree(vector < vector<int> > & log_frquence)
{
    /**
    //������Ƶ����� ���F-list

    //��ÿ����ѯ��·���� ����Ƶ���� ��ɾ����Ƶ����
    vector<vector<int> > log_frquence;//���vector���ÿ��log��¼���ڲ�vector���log��¼�Ĳ�ѯ·��

    //test
    vector<int> read;
    int n,m,k;
    cin>>n;
    while(n--)
    {
        cin>>m;
        read.clear();
        for(int i=0;i<m;i++)
        {
            cin>>k;
            if(Flist_glb[k].head==NULL)
            {
                Flist_glb[k].support=1;
                Flist_glb[k].head=NULL;
            }
            else
                ++Flist_glb[k].support;
            read.push_back(k);
        }
        log_frquence.push_back(read);
    }
    cout<<"read"<<endl;
    */
    //����
    FP_Node *root=(FP_Node *)malloc(sizeof(FP_Node));
    if(root==NULL)
    {
        cout<<"root memalloc error"<<endl;
        return -1;
    }
    root->l_child=root->r_child=root->father=root->pre_item=NULL;

    if(!build_tree(root,log_frquence))
    {
        cout<<"build fp tree error!"<<endl;
        return -1;
    }
    cout<<"build"<<endl;
    fp_print(root->l_child);
    flist_print(Flist_glb);
    vector<int> alpha;
    FP_growth(root,Flist_glb,alpha);

    map<int,Flist>::iterator it;
    return 0;
}
