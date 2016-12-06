class Rect
{
public:
	int _left;
	int _top;
	int _right;
	int _bottom;
	static int _count;
public:
	Rect(int left, int top, int right, int bottom);
	~Rect();
};

int Rect::_count = 0;

int main()
{
	int sum = 0;
	int cnt = 1;
	while(cnt <= 100){
		sum += cnt;
		if(cnt <= 50)
			cnt = cnt + 2;
		else
			cnt = cnt + 1;
	}
	return 0;
}
