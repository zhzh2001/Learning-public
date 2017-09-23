#include <cstdio>
#include <string>
#include <cctype>
#include <cstdlib>
#include <windows.h>
struct Istream
{
  private:
	HANDLE hFile;
	char *base, *p;
	bool good;

	void fetch()
	{
		if (hFile == INVALID_HANDLE_VALUE)
			good = false;
		else
		{
			HANDLE hFileMappingObject = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
			if (!hFileMappingObject)
				good = false;
			else
				base = p = (char *)MapViewOfFile(hFileMappingObject, FILE_MAP_READ, 0, 0, 0);
		}
	}

	char nextchar()
	{
		/* if(!*p)
		{
			good=false;
			return 0;
		} */
		return *p++;
	}

	template <typename Int>
	void readint(Int &x)
	{
		char c;
		for (c = nextchar(); isspace(c); c = nextchar())
			;
		x = 0;
		Int sign = 1;
		if (c == '-')
			sign = -1, c = nextchar();
		for (; isdigit(c); c = nextchar())
			x = x * 10 + c - '0';
		x *= sign;
	}

  public:
	Istream() : hFile(NULL), p(NULL), good(false) {}

	explicit Istream(const std::string &filename) : hFile(CreateFile(filename.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)), p(NULL), good(false)
	{
		fetch();
	}

	bool close()
	{
		return UnmapViewOfFile(base) && CloseHandle(hFile);
	}

	~Istream()
	{
		close();
	}

	operator bool() const
	{
		return good;
	}

	bool operator!() const
	{
		return !good;
	}

	bool open(const std::string &filename)
	{
		hFile = CreateFile(filename.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		fetch();
		return good;
	}

	Istream &operator>>(short &value)
	{
		readint(value);
		return *this;
	}

	Istream &operator>>(unsigned short &value)
	{
		readint(value);
		return *this;
	}

	Istream &operator>>(int &value)
	{
		readint(value);
		return *this;
	}

	Istream &operator>>(unsigned int &value)
	{
		readint(value);
		return *this;
	}

	Istream &operator>>(long &value)
	{
		readint(value);
		return *this;
	}

	Istream &operator>>(unsigned long &value)
	{
		readint(value);
		return *this;
	}

	Istream &operator>>(long long &value)
	{
		readint(value);
		return *this;
	}

	Istream &operator>>(unsigned long long &value)
	{
		readint(value);
		return *this;
	}

	Istream &operator>>(char &c)
	{
		for (c = nextchar(); isspace(c); c = nextchar())
			;
		return *this;
	}

	Istream &operator>>(std::string &s)
	{
		char c;
		for (c = nextchar(); isspace(c); c = nextchar())
			;
		s.clear();
		for (; good && !isspace(c); c = nextchar())
			s += c;
		return *this;
	}

	Istream &operator>>(double &value)
	{
		std::string s;
		*this >> s;
		value = atof(s.c_str());
		return *this;
	}

	friend Istream &getline(Istream &is, std::string &s, char delim = '\n');
};

Istream &getline(Istream &is, std::string &s, char delim)
{
	char c;
	s.clear();
	for (c = is.nextchar(); is.good && c != delim; c = is.nextchar())
		s += c;
	return is;
}

struct Ostream
{
  private:
	static const size_t defaultBufsz = 1e6;
	FILE *stream;
	size_t bufsz;
	char *buf, *p, dig[25];

  public:
	Ostream() : stream(NULL), bufsz(defaultBufsz), buf(NULL), p(NULL) {}

	explicit Ostream(const std::string &filename, size_t bufsz = defaultBufsz) : stream(fopen(filename.c_str(), "w")), bufsz(bufsz), buf(new char[bufsz]), p(buf) {}

	explicit Ostream(FILE *stream, size_t bufsz = defaultBufsz) : stream(stream), bufsz(bufsz), buf(new char[bufsz]), p(buf) {}

	bool close()
	{
		return !fclose(stream);
	}

	void flush()
	{
		fwrite(buf, 1, p - buf, stream);
		p = buf;
	}

  private:
	void writechar(char c)
	{
		*p++ = c;
		if (p == buf + bufsz)
			flush();
	}

	template <typename Int>
	void writeint(Int x)
	{
		if (x < 0)
			writechar('-'), x = -x;
		int len = 0;
		do
			dig[++len] = x % 10;
		while (x /= 10);
		for (; len; len--)
			writechar(dig[len] + '0');
	}

  public:
	~Ostream()
	{
		flush();
		close();
		delete[] buf;
	}

	bool open(const std::string &filename, size_t bufsz = defaultBufsz)
	{
		stream = fopen(filename.c_str(), "w");
		this->bufsz = bufsz;
		delete[] buf;
		p = buf = new char[bufsz];
		return stream;
	}

	bool open(FILE *stream, size_t bufsz = defaultBufsz)
	{
		this->stream = stream;
		this->bufsz = bufsz;
		delete[] buf;
		p = buf = new char[bufsz];
		return stream;
	}

	Ostream &operator<<(short value)
	{
		writeint(value);
		return *this;
	}

	Ostream &operator<<(unsigned short value)
	{
		writeint(value);
		return *this;
	}

	Ostream &operator<<(int value)
	{
		writeint(value);
		return *this;
	}

	Ostream &operator<<(unsigned int value)
	{
		writeint(value);
		return *this;
	}

	Ostream &operator<<(long value)
	{
		writeint(value);
		return *this;
	}

	Ostream &operator<<(unsigned long value)
	{
		writeint(value);
		return *this;
	}

	Ostream &operator<<(long long value)
	{
		writeint(value);
		return *this;
	}

	Ostream &operator<<(unsigned long long value)
	{
		writeint(value);
		return *this;
	}

	Ostream &operator<<(char c)
	{
		writechar(c);
		return *this;
	}

	Ostream &operator<<(const std::string &s)
	{
		for (size_t i = 0; i < s.length(); i++)
			writechar(s[i]);
		return *this;
	}

	Ostream &operator<<(Ostream &(*func)(Ostream &))
	{
		return func(*this);
	}

	friend Ostream &endl(Ostream &os);
};

Ostream &endl(Ostream &os)
{
	os.writechar('\n');
	return os;
}

Istream fin("paint.in");
Ostream fout("paint.out");
const int N = 5000005;
int f[N];
int getf(int x)
{
	return f[x] == x ? x : f[x] = getf(f[x]);
}
int main()
{
	int n, m;
	fin >> n >> m;
	for (int i = 0; i <= n; i++)
		f[i] = i;
	while (m--)
	{
		int l, r;
		fin >> l >> r;
		while (l <= r)
			if (getf(r) == r)
			{
				f[r--] = getf(l - 1);
				n--;
			}
			else
				r = getf(r);
		/*
		while (getf(r) != getf(l - 1))
		{
			f[getf(r)] = getf(r) - 1;
			n--;
		}
		*/
		fout << n << endl;
	}
	return 0;
}