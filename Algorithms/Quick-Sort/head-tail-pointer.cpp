int q[N];

void quick_sort(int q[], int b, int e) {
	if (b >= e) return;

	int p = q[(b+e)/2];

	int i = b - 1, j = e + 1;

	/*
	 * In case we use 'j' as the split point, the pivot must not be the index
	 * 'e'.
	 *
	 * If there's a chance the pivot becomes 'q[e]', then there's a possibility
	 * that after the loop, 'j' will be set to 'e'.
	 * In such a case, we might end up in an infinite recursive call of
	 * quick_sort(b, j).
	 */

	while (i < j) {
		do i++; while (q[i] < p);
		do j--; while (q[j] > p);
		if (i < j) swap(q[i], q[j]);
	}

	quick_sort(q, b, j);
	quick_sort(q, j + 1, e);

	return;
}