ll solve_triangle(ll A, ll B, ll C) {//x,y >=0, Ax+By<=C
    if (C < 0) return 0;
    if (A > B) swap(A, B);
    ll p = C / B;
    ll k = B / A;
    ll d = (C - p * B) / A;
    return solve_triangle(B - k * A, A, C - A * (k * p
        + d + 1)) + (p + 1) * (d + 1) + k * p * (p
            + 1) / 2;
}
