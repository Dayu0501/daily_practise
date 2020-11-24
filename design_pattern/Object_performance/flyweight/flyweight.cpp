/*
 * flyweight 享元模式，就是池技术
 */

#include <string>
#include <map>

using namespace std;

class Font {
private:

	//unique object key
	string key;

	//object state
	//....

public:
	Font(const string &key) {
		//...
	}
};

/* 字体池，使用的时候就从池中拿一个 */
class FontFactory {
private:
	map<string, Font *> fontPool;

public:
	Font *GetFont(const string &key) {

		map<string, Font *>::iterator item = fontPool.find(key);

		if (item != fontPool.end()) {
			return fontPool[key];
		} else {
			Font *font = new Font(key);
			fontPool[key] = font;
			return font;
		}

	}

	void clear() {
		//...
	}
};