// Segment tree with lazy propagation for both update and assignment

class SegTree{
    public :
    vector<ll> t;
    vector<pair<ll,ll>> d;
    void initialize(int sz){
        t.resize(4*sz);
        d.resize(4*sz);
    }
    void build(int v,int l,int r,vector<int> &a){
        if(l==r){
            t[v]=a[l];
            return ;
        }
        int mid=(l+r)/2;
        build(2*v,l,mid,a);
        build(2*v+1,mid+1,r,a);
        t[v]=t[2*v]+t[2*v+1];
    }
    void push(int v,int l,int r){
        // type 1 for addition
        // type 2 for assignment
        if(d[v].ff==1){
            t[v]+=(r-l+1)*d[v].ss;
            if(l!=r){
                d[2*v].ss+=d[v].ss;
                d[2*v+1].ss+=d[v].ss;
                d[2*v].ff=max(d[2*v].ff,1ll);
                d[2*v+1].ff=max(d[2*v+1].ff,1ll);
            }
            d[v].ff=0;
            d[v].ss=0;
        }
        else if(d[v].ff==2){
            t[v]=(r-l+1)*d[v].ss;
            if(l!=r){
                d[2*v].ss=d[v].ss;
                d[2*v+1].ss=d[v].ss;
                d[2*v].ff=2;
                d[2*v+1].ff=2;
            }
            d[v].ff=0;
            d[v].ss=0;
        }
    }
    void upd(int v,int l,int r,int a,int b,int typ,ll x){
        push(v,l,r);
        if(l>r||l>b||r<a){
            return ;
        }
        if(l>=a&&r<=b){
            if(typ==1){
                d[v].ff=1;
                d[v].ss=x;
            }
            else{
                d[v].ff=2;
                d[v].ss=x;
            }
            push(v,l,r);
            return ;
        }
        int mid=(l+r)/2;
        upd(2*v,l,mid,a,b,typ,x);
        upd(2*v+1,mid+1,r,a,b,typ,x);
        t[v]=t[2*v]+t[2*v+1];
    }
    ll query(int v,int l,int r,int a,int b){
        push(v,l,r);
        if(l>r||l>b||r<a){
            return 0;
        }
        if(l>=a&&r<=b){
            return t[v];
        }
        int mid=(l+r)/2;
        ll sum=query(2*v,l,mid,a,b);
        sum+=query(2*v+1,mid+1,r,a,b);
        return sum;
    }
};
