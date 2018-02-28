#pragma once
class DisplayableObject
{
public:
	DisplayableObject();
	~DisplayableObject();

	virtual void Render() = 0;
	virtual void Update() = 0;

};

