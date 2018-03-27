#pragma once
class AnimationFrame
{
public:
	AnimationFrame(long runtime);
	virtual ~AnimationFrame();

	virtual void Render() = 0;

	inline long GetRuntime() const
	{
		return runTime;
	}

private:
	const long runTime;


};

