const int iters = 8;// можно уменьшить
bool isprime(ll p)
{
	if (p == 1 || p == 4) return 0;
	if (p == 2 || p == 3) return 1;
	for (int it = 0; it < iters; ++it)
	{
		ll a = rnd() % (p - 2) + 2;
		ll nw = p - 1;
		while (nw % 2 == 0)nw /= 2;
		ll x = binpow(a, nw, p);//int128
		if (x == 1)continue;
		ll last = x;
		nw *= 2;
		while (nw <= p - 1)
		{
			x = (__int128_t)x * x % mod;
			if (x == 1)
			{
				if (last != p - 1)
				{
					return 0;
				}
				break;
			}
			last = x;
			nw *= 2;
		}
		if (x != 1) return 0;
	}
	return 1;
}
