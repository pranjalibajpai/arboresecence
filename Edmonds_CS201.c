#include <stdio.h>
#include<stdlib.h>
#include <sys/time.h>	// for gettimeofday()
int time=0,cycle=0;
struct node
{
    int w,label,ls;
    struct node*next;
    
};
struct head
{
	int nlabel;
    struct node*nex;
};
struct dfsnode
{
	int label,state,parent,d,f;
};
int minimum(struct head final[],int dist[],int n,int s)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(final[i].nlabel==s)
        break;
    }
    struct node*t;
    t=final[i].nex;
    while(t!=NULL)
    {
       dist[t->label-1]=dist[final[i].nlabel-1]+t->w;
       minimum(final,dist,n,t->label);
       t=t->next;
    }
    return 0;
}
int add(struct node**a,int u,int wei,int lsu)
{
    struct node*temp;
    temp=(struct node*)malloc(sizeof(struct node));
    temp->w=wei;
    temp->label=u;
    temp->ls=lsu;
    temp->next=NULL;
    //first
    if((*a)==NULL)
    (*a)=temp;
    else
    {
        struct node*t;
        t=(*a);
        while(t->next!=NULL)
         t=t->next;
         t->next=temp;
    }
    return 0;
}
int dfs(int i,struct head zero[],struct dfsnode node[],int n,int cnode[])		
{
	int v,j,k;//check index matches 
	node[i].state=1;
	time=time+1;
	node[i].d=time;
	struct node *t;
	t=zero[i].nex;				
	while(t!=NULL)
	{
		for(j=0;j<n;j++)
		{
			if(t->label==node[j].label)
			break;
		}
		if(node[j].state==0)
		{
			node[j].parent=node[i].label;
			dfs(j,zero,node,n,cnode);
		}
		else if(node[j].state==1)
		{
			for(k=0;k<n;k++)
			//copy the present state to cnode
			if(cycle==0)
			{
				for(k=0;k<n;k++)
				cnode[k]=node[k].state;
			}
			cycle=1;
		}
		t=t->next;
	}
	node[i].state=2;
	time=time+1;
	node[i].f=time;
	return 0;
}
int arbo(struct head o[],int n,int nn,int s,struct head min[],struct head m[],int rec,struct head ori[],int expand,int countt,struct head mm[])
{
   // printf("arbo called\n");
	struct node *temp,*t1,*t2;
	int i=0,flag=0,count=0,cy=0,k=0,j=0,x=0,y=0;

	for(k=0;k<n;k++)
	{
		m[k].nex=NULL;
		m[k].nlabel=-1;
	}
	for(i=0;i<n;i++)
	{
		m[i].nlabel=o[i].nlabel;
	}
	//printf("find minimum cost entering edge for each node\n");
	if(rec==0)
	{
     	for(i=0;i<n;i++)
		{
		    temp=o[i].nex;
			if(temp!=NULL)
			{
				min[i].nlabel=o[i].nlabel;
			    m[i].nlabel=o[i].nlabel;
				add(&min[i].nex,temp->label,temp->w,temp->ls);
				add(&m[i].nex,temp->label,temp->w,temp->ls);	
				t1=min[i].nex;
				t2=m[i].nex;
				temp=temp->next;
				while(temp!=NULL)
				{
				    //when edge weights are same then 
					if(temp->w==t1->w && temp->w==t2->w)
					{
						t1->label=temp->label;
						t2->label=temp->label;
					}
					if(temp->w<t1->w && temp->w<t2->w)
					{
						t1->label=temp->label;
						t2->label=temp->label;
						t1->w=temp->w;
						t2->w=temp->w;					
					}
					temp=temp->next;
				}	
			}
		}		
	}
	else
	{
     	for(i=0;i<n;i++)
		{
		    temp=o[i].nex;
			if(temp!=NULL)
			{
				m[i].nlabel=o[i].nlabel;
				add(&m[i].nex,temp->label,temp->w,temp->ls);	
				t2=m[i].nex;
				temp=temp->next;
				while(temp!=NULL)
				{
				    //when edge weights are same then 
					if(temp->w==t2->w)
					{
						t2->label=temp->label;
					}
					if(temp->w<t2->w)
					{
						t2->label=temp->label;
						t2->w=temp->w;					
					}
					temp=temp->next;
				}	
			}
		}		
	}
//	printf("update reduced cost subtract min\n"); 
	for(i=0;i<n;i++)
	{
	    temp=o[i].nex;
		if(temp!=NULL)
		{
			t1=m[i].nex;
			while(temp!=NULL)
			{
				temp->w=temp->w-t1->w;
				temp=temp->next;
			}
		}
	}
	//printf("form list of zero weight\n");
	struct head zero[n];
	for(i=0;i<n;i++)
	{
		zero[i].nex=NULL;
		zero[i].nlabel=m[i].nlabel;			
	}
	for(i=0;i<n;i++)
	{
		t1=m[i].nex;
		
		if(t1!=NULL){
		    for(k=0;k<n;k++)
		    {
		        if(zero[k].nlabel==t1->label)
		        break;
		    }
			add(&zero[k].nex,m[i].nlabel,t1->w,-1);}
	}
	struct dfsnode node[n];
	int cnode[n];
	cycle=0;
	for(i=0;i<n;i++)
	{
		cnode[i]=0;
		node[i].state=0;
		node[i].parent=-1;
		node[i].label=m[i].nlabel;	
		node[i].d=-1;
		node[i].f=-1;		
	} 
	for(i=0;i<n;i++)
	{
		temp=zero[i].nex;
		if(temp!=NULL && node[i].state==0)
		{
			for(k=0;k<n;k++)
			{
				if(m[k].nlabel==node[i].label)
				{
					t1=m[k].nex;
					if(t1!=NULL)
					{
					    node[i].parent=t1->label;
					    break;
					}
				}
			}
		    dfs(i,zero,node,n,cnode);
		}
	}
	for(k=0;k<n;k++)
	{
		 if(cnode[k]==1)
		 cy++;
	}
	if(cycle==1)
	{
		//form supernode
		struct head newh[n-cy+1];
		for(i=0;i<n-cy+1;i++)
			newh[i].nex=NULL;
		i=0;
		for(k=0;k<n;k++)
		{
		    if(cnode[k]!=1)
		    {
		    	newh[i].nlabel=node[k].label;
		    	i++;
		    }
		}
		newh[n-cy].nlabel=nn+rec+1;
		for(i=0;i<n;i++)
		{
			if(cnode[i]!=1)
			{
				t1=o[i].nex;
				if(t1==NULL)
				newh[i].nex=NULL;
				else if(t1!=NULL)
				{
					while(t1!=NULL)
					{
						for(k=0;k<n;k++)
						{
							if(node[k].label==t1->label)
							break;
						}
						if(cnode[k]!=1)
						{
							for(x=0;x<n-cy+1;x++)
							{
								if(newh[x].nlabel==o[i].nlabel)
								break;
							}
							add(&newh[x].nex,t1->label,t1->w,-1);
						}
						else if(cnode[k]==1)
						{
							for(y=0;y<n-cy+1;y++)
							{
								if(newh[y].nlabel==o[i].nlabel)
								break;
							}
							add(&newh[y].nex,nn+rec+1,t1->w,t1->label);
						}
						t1=t1->next;
					}
				}
		  }
		  else if(cnode[i]==1)
		   	{
				t1=o[i].nex;	
				if(t1==NULL)
				newh[i].nex=NULL;
				else if(t1!=NULL)
				{
					 while(t1!=NULL)
					 {
					 	for(j=0;j<n;j++)
					 	{
					 		if(node[j].label==t1->label)
					 		break;
					 	}
					 	if(cnode[j]!=1)
					 	{
					 		add(&newh[n-cy].nex,t1->label,t1->w,o[i].nlabel);
					 	}
					 	t1=t1->next;
					 }
				}
			}
		}
	//	printf("supernode\n");
		for(i=0;i<n-cy+1;i++)
		{
			t1=newh[i].nex;
			while(t1!=NULL)
			{
				t1=t1->next;
			}
		}
		int index=nn+rec+1;
		rec++;
		arbo(newh,n-cy+1,nn,s,min,m,rec,ori,expand,countt,m);

		//printf("expand supernode\n");
		expand=1;
		if(expand==1 && rec==1)
		{
		    if(n==nn)          
	    	{
		         for(i=0;i<n-cy+1;i++)
		         {
		   	          if(m[i].nlabel==index)
	        	    	break;
		         }
    	    	t1=m[n-cy].nex;
		        temp=newh[n-cy].nex;
    	    	while(temp!=NULL)
	        	{
		         	if(temp->w==0 && t1->label==temp->label)
			       break;
		    	    temp=temp->next;
	        	}
    	    	if(temp!=NULL)
	        	{
        	    	for(i=0;i<n;i++)
        	    	{
                        if(temp->ls==min[i].nlabel)
                      break;
        	    	}
        	    	t2=min[i].nex;
             		//update weight and label
        	    	t2->label=temp->label;
        	    	t2->w=temp->w;
		        }
	    	} 
		}

	}
	else if(cycle==0)
	{
		return 0;		
	}
	return 0;
}
int main(void) {
    struct timeval start, end;
	gettimeofday(&start, NULL);
	int test,te;
	scanf("%d",&test);
	for(te=0;te<test;te++)
	{
		time=0;
	    int n,s,e,u,v,w,i,flag=0,ce=0,rec=0,tmc=0;
	    scanf("%d %d",&n,&s);
	    scanf("%d",&e);
	    struct head h[n],o[n],min[n],m[n],super[n],mm[n];
	    struct node *t,*t1;
	    for(i=0;i<n;i++)
	   {
	       h[i].nex=super[i].nex=NULL;
	       o[i].nex=NULL; 
	       h[i].nlabel=i+1;
	       mm[i].nex=NULL;
	       o[i].nlabel=i+1;
	       min[i].nex=NULL;
	       m[i].nex=NULL;  
	   }
	   for(i=0;i<e;i++)
	   {
	       flag=0;
	       scanf("%d %d %d",&u,&v,&w);
	       //check whether edge is already added or not(duplicate entry)
	       t=h[v-1].nex;
	       if(t==NULL)
	       {
             	add(&h[v-1].nex,u,w,-1);
	        	add(&o[v-1].nex,u,w,-1);
	        }
	        else
	        {
	        	while(t!=NULL)
	        	{
	        		if(t->label==u)
	        		{
	        			if(w<t->w)
	        			t->w=w;
	        			flag=1;
	        			ce++;
	        			break;
	        		}	
	        		t=t->next;
	        	}
	        	if(flag==0)
	        	{
	        		add(&h[v-1].nex,u,w,-1);
	        		add(&o[v-1].nex,u,w,-1);
	        	}
	        }
	    }
	    n=n-ce;      //if duplicate edges are found

	    arbo(o,n,n,s,min,m,rec,h,0,0,mm);
	    int dist[n];
	    struct head final[n];
	    for(i=0;i<n;i++)
	    {
	        dist[i]=-1;
	        final[i].nex=NULL;
	        final[i].nlabel=i+1;
	    } 
	    dist[s-1]=0;
	    for(i=0;i<n;i++)
	    {
	        t=min[i].nex;
	        if(t!=NULL)
	        {
	            t1=h[i].nex;
	            while(t1!=NULL)
	            {
	                if(t1->label==t->label)
	                {
	                    //printf("t1->w %d i+1= %d t1->label %d \n",t1->w,i+1,t1->label);
	                    add(&final[t1->label-1].nex,i+1,t1->w,-1);
	                    tmc+=t1->w;
	                    break;
	                }
	                t1=t1->next;
	            }
	        }
	    }
	    printf("%d ",tmc); 
	    minimum(final,dist,n,s);
	    for(i=0;i<n;i++)
	    printf("%d ",dist[i]);
	    //shortest distance
	    printf("# ");
	    //parent
	    for(i=0;i<n;i++)
	    {
	        if(i==s-1)
	        printf("0 ");
	        else
	        {
	            t1=min[i].nex;
	            if(t1==NULL)
	            printf("-1 ");
	            else
	            printf("%d ",t1->label);
	        }
	    }
	    printf("\n");
	}
	gettimeofday(&end, NULL);
	long seconds = (end.tv_sec - start.tv_sec);
	long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
	printf("Time elpased is %ld seconds and %ld micros\n", seconds, micros);
	return 0;
}

/*
3
5 1
5
1 2 4
2 3 3
3 4 1 
1 5 5
2 5 2
4 1
4
1 2 3
1 3 4
1 4 5
2 4 6
5 1
5
1 2 3
2 3 1
3 4 1
4 2 1
4 5 6
10 0 4 7 8 6 # 0 1 2 3 2
12 0 3 4 5 # 0 1 1 1 
11 0 3 4 5 11 # 0 1 2 3 4 
Time elpased is 0 seconds and 224258 micros

*/

