#include <Papyrus.h>



class PapyrusApp : public Papyrus::Application
{
public:
	PapyrusApp() {}
	~PapyrusApp() {} 

};

Papyrus::Application* Papyrus::createApplication()
{
	return new PapyrusApp();
}
