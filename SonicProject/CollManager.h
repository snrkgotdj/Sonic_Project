#pragma once

class Collider;
class CollManager
{
private:
	vector<ColPair> VecColPair;
	map<DWORD, bool> mapColID;
private:
	bool Collision(Collider* _left, Collider* _right);

public:
	void update();
	void SetColPair(ColPair _pair) { VecColPair.push_back(_pair); }
	void clear();
public:
	static CollManager& Manager()
	{
		static CollManager inst;
		return inst;
	}
private:
	CollManager();
	~CollManager();
};

