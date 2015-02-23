#pragma once


// fwd decls
struct GLFWwindow;

class TestBed
{
public:
	TestBed();
	~TestBed();

	bool Init();
	bool Update() const;
	void Stop();

private:
	bool isValid;
	GLFWwindow* pWindow;
};

