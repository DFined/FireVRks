#include "Util/DFAnchor.h"

UDFAnchor* UDFAnchor::Instance()
{
	auto Anchor = NewObject<UDFAnchor>(GetTransientPackage(), "DFStaticOuterAnchor");
	Anchor->AddToRoot();
	return Anchor;
}

void UDFAnchor::Anchor(UObject* Object)
{
	Children.Add(Object);
}
