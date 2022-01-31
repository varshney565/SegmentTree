class SegTree{
public:
    vector<int> p;
    vector<int> v;
    SegTree(vector<int> &v){
        int n = v.size();
        p.resize(4*n,0);
        this->v.assign(v.begin(),v.end());
    }

    //query for [l,r]
    int query(int index,int l,int r,int low,int high){
        //No overlap
        //[l,r] [low,high] or [low,high] [l,r]
        
        /*---------------------------------*/
        if(r < low || high < l)
            return 0;               //depends on question
        /*---------------------------------*/


        //Complete Overlap
        //[l...low...high...r]
        if(l <= low && r >= high)
            return p[index];



        //Partial Overlap
        //[low...l...r...high] or [low....l...high...r] or [l...low...r....high]
        int mid = low+(high-low)/2;
        int left = query(2*index+1,l,r,low,mid);
        int right = query(2*index+2,l,r,mid+1,high);
        /*---------------------------------*/
        return left+right;          //depends on question
        /*---------------------------------*/
    }

    void update(int index,int low,int high,int i,int val){
        if(low == high){
            v[i] = val;
            p[index] = val;
        }

        int mid = low+(high-low)/2;
        if(i <= mid)
            update(2*index+1,low,mid,i,val);
        else
            update(2*index+2,mid+1,high,i,val);
        /*---------------------------------*/
        p[index] = p[2*index+1]+p[2*index+2];  //depends on question
        /*---------------------------------*/
    }

    void build(int index,int low,int high){
        if(low == high){
            p[index] = v[low];
            return;
        }

        int mid = low+(high-low)/2;
        build(2*index+1,low,mid);
        build(2*index+2,mid+1,high);
        p[index] = p[2*index+1]+p[2*index+2];
    }
};
