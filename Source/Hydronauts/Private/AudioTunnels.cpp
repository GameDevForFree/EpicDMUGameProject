


#include "AudioTunnels.h"
#include "Kismet/GameplayStatics.h"

AAudioTunnels::AAudioTunnels()
{
	
	PrimaryActorTick.bCanEverTick = true;


	AudioMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AudioMesh"));
	RootComponent = AudioMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
		TEXT("/Game/Project_Assets_FBX_OBJ/PowerUp_ButtonSpawnObjects/AudioBox/Book1_Open.Book1_Open")
	);

	if (MeshAsset.Succeeded())
	{
		AudioMesh->SetStaticMesh(MeshAsset.Object);
		AudioMesh->SetVisibility(true);
		AudioMesh->SetWorldScale3D(FVector(1.f));
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Audio/tunnelslevelmusicend2.tunnelslevelmusicend2"));
	if (SoundAsset.Succeeded())
		AudioTunnelSFX = SoundAsset.Object;

}


void AAudioTunnels::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySoundAtLocation(this, AudioTunnelSFX, GetActorLocation());
	
}


void AAudioTunnels::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

