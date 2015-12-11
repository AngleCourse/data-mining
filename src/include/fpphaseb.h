#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <stack>
#include <map>

//#include <preprocessing.h> 预处理头文件
using namespace std;
int GLB_SUP=10000;
int GLB_CONF=10000;

typedef struct FP_Node
{
    int ip_id;
    struct FP_Node *l_child;//儿子
    struct FP_Node *r_child;//兄弟
    struct FP_Node *father;//父亲节点
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
    FP_Node *cur;//当前节点
    int cur_ip;
    for(int j=0;j<log_vec.size();j++)
    {
        cur = p->l_child;
        cur_ip = log_vec[j];
        if(!p->l_child)//左儿子空，新建节点
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
            //头插法法构建index
            cur->pre_item=Flist[cur_ip].head;
            Flist[cur_ip].head=cur;
            p=cur;
        }
        else if(cur->ip_id==cur_ip)//判断是否在在此节点
        {
            cur->support+=sup;
            p=cur;
        }
        else//查找右兄弟
        {
            p=cur;
            while((cur=cur->r_child))//兄弟节点
            {
                if(cur->ip_id==cur_ip)
                {
                    cur->support+=sup;
                    p=cur;
                    break;
                }
                p=cur;
            }
            if(!cur)//空节点
            {
                if(!(p->r_child=(FP_Node *)malloc(sizeof(FP_Node))))//新建右兄弟
                {
                    cout<<"rson stack error!!!"<<endl;
                    return false;
                };
                cur=p->r_child;
                cur->father=p->father;//父节点指向兄弟节点的父节点
                cur->l_child=cur->r_child=NULL;
                cur->ip_id=cur_ip;
                cur->support=sup;
                 //头插法法构建index
                cur->pre_item=Flist[cur_ip].head;
                Flist[cur_ip].head=cur;

                p=cur;
            }
        }
    }
}

void FP_free(FP_Node * root)//释放fp树内存
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
    FP_Node *p;//当前节点的父节点
    FP_Node *cur;//当前节点
    int cur_ip;

    for(int i=0;i<log_frquence.size();i++)
    {
        p=root;
        vector<int> log_vec=log_frquence[i];
        insert_link(p,log_vec,Flist_glb,1);//初始化每件物品支持度计数为1
    }
    return true;
}

int FP_growth(FP_Node * root, map<int,Flist> &head_table, vector<int>&alpha)
{
    bool signal_link=true;
    FP_Node *cur = root;
    while(cur->l_child!=NULL)//判断是否为单个路径
    {
        cur=cur->l_child;
        if(cur->r_child!=NULL)
        {
            signal_link = false;//不是单链
            break;
        }
    }
    if(signal_link)
    {
        return -1;//返回频繁项集
    }
    else
    {

        map<int,Flist>::iterator it;
        for(it=head_table.begin();it!=head_table.end();++it)
        {
            FP_Node *index=(*it).second.head;
            /*
             *在此生成 beta = i U alpha
             ...
             */

            vector<int> beta(alpha);
            beta.push_back(index->ip_id);

            // beta.push_back(ip_id);
            /*
             *构造节点i的条件FP树,FP_Node ,Flist
             */

            FP_Node *cond_fp=(FP_Node *)malloc(sizeof(FP_Node));
            if(cond_fp==NULL)
            {
                cout<<"cond_fp malloc error"<<endl;
                return -1;
            }
            cond_fp->l_child=cond_fp->r_child=NULL;

            vector <int> cond_log;//条件FP树的条件模式基
            map<int, Flist>cond_Flist;//条件FP树的Flist
            cond_Flist.clear();


            FP_Node *par;//表示条件模式基的路径上的节点

            for(;index!=NULL;index=index->pre_item)
            {
               stack<FP_Node*> cond_pattern;//index的条件模式基链

              par=index;
               while(par=par->father)
               {
                   cond_pattern.push(par);
               }
               cond_log.clear();
               cond_pattern.pop();//去除NULL节点
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

               insert_link(cond_fp,cond_log,cond_Flist,index->support);//初始化每件物品支持度计数为1
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
    //对事物频繁项处理 输出F-list

    //对每个查询链路处理 排序频繁项 ，删除不频繁项
    vector<vector<int> > log_frquence;//外层vector存放每条log记录，内层vector存放log记录的查询路径

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
    //建树
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
