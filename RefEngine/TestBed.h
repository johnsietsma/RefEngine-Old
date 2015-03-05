#pragma once

#include <memory>

// fwd decls
class RefEngine;

class TestBed
{
public:
	TestBed();

	bool Update(double deltaTime);
	void Draw() const;
	void Stop();

private:
	std::shared_ptr<RefEngine> m_pRefEngine;
};

