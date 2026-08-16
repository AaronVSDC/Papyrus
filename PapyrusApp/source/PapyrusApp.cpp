#include <Papyrus.h>



class PapyrusApp final : public Papyrus::Application
{
public:
	PapyrusApp() = default;
	~PapyrusApp() override = default;

};

Papyrus::Application* Papyrus::createApplication()
{
	return new PapyrusApp();
}
