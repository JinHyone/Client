#pragma once

class Compoent;
class Collider;

class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetPos(Vec2 pos) { _pos = pos; }
	Vec2 GetPos() { return _pos; }

	void SetLayer(LAYER_TYPE layer) { _layer = layer; }
	LAYER_TYPE GetLayer() { return _layer; }

	void AddCompoent(Compoent* compoent);
	void RemoveCompoent(Compoent* compoent);

	virtual void OnCollisionEnter(Collider* src, Collider* dest);
	virtual void OnCollisionExit(Collider* src, Collider* dest);

protected:
	Vec2 _pos = { 0.f, 0.f };
	Vec2 _destPos = { 0.f, 0.f };
	LAYER_TYPE _layer = LAYER_OBJECT;
	vector<Compoent*> _compoents;
};

