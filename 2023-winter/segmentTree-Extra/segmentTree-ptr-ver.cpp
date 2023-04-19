// by. MiohitoKiri5474
#include<bits/stdc++.h>

using namespace std;

struct node {
	node *l, *r;
	int value;

	node ( int _val ): l ( nullptr ), r ( nullptr ), value ( _val ) {}

	inline void up ( void ) {
		value = -1;
		if ( l )
			value = max ( value, l -> value );
		if ( r )
			value = max ( value, r -> value );
	}
} *seg = nullptr;

void build ( int l, int r, node *&o ) {
	o = new node ( 0 );
	if ( l == r )
		return;
	int mid = ( l + r ) >> 1;
	build ( l, mid, o -> l );
	build ( mid + 1, r, o -> r );

	o -> up();
}

void update ( int l, int r, int index, int value, node *&o ) {
	if ( l == r )
		o -> value = value;
	else{
		int mid = ( l + r ) >> 1;
		if ( index <= mid )
			update ( l, mid, index, value, o -> l );
		else
			update ( mid + 1, r, index, value, o -> r );

		o -> up();
	}
}

int query ( int l, int r, int nowL, int nowR, node *o ) {
	if ( l <= nowR && nowR <= r )
		return o -> value;
	int mid = ( nowL + nowR ) >> 1;
	if ( r <= mid )
		return query ( l, r, nowL, mid, o -> l );
	if ( mid < l )
		return query ( l, r, mid + 1, nowR, o -> r );

	return max ( query ( l, r, nowL, mid, o -> l ), query ( l, r, mid + 1, nowR, o -> r ) );
}

int main() {
	ios::sync_with_stdio ( false );
	cin.tie ( 0 );
	cout.tie ( 0 );

	int n, m, l, r, in, type;
	cin >> n >> m;
	build ( 1, n, seg );
	for ( int i = 1 ; i <= n ; i++ ){
		cin >> in;
		update ( 1, n, i, in, seg );
	}

	// type 1: 單點修改
	// type 2: 區間查詢最大值
	while ( m-- ) {
		cin >> type;
		if ( type == 1 ) {
			cin >> l >> in;
			update ( 1, n, l, in, seg );
		}
		else if ( type == 2 ) {
			cin >> l >> r;
			cout << query ( l, r, 1, n, seg ) << '\n';
		}
	}
}
