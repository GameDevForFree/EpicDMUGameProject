// All code here is by Alex Robertson P2607829

#include "AudioTunnels.h"
#include "Kismet/GameplayStatics.h"

AAudioTunnels::AAudioTunnels()
{
	
	PrimaryActorTick.bCanEverTick = true;


	// creates a mesh component and sets it as the root component of the actor

	AudioMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AudioMesh"));
	RootComponent = AudioMesh;

	// loads the 3D mesh onto the component with the given file path

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
		TEXT("/Game/Project_Assets_FBX_OBJ/PowerUp_ButtonSpawnObjects/AudioBox/Book1_Open.Book1_Open")
	);

	// sets the mesh to component if successful, sets visiblity and scale also

	if (MeshAsset.Succeeded())
	{
		AudioMesh->SetStaticMesh(MeshAsset.Object);
		AudioMesh->SetVisibility(true);
		AudioMesh->SetWorldScale3D(FVector(1.f));
	}

	// finds specified audio file and assigns it to the variable which is a SoundAsset object

	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Audio/tunnelslevelmusicend2.tunnelslevelmusicend2"));
	if (SoundAsset.Succeeded())
		AudioTunnelSFX = SoundAsset.Object; 

}


void AAudioTunnels::BeginPlay()
{
	Super::BeginPlay();

	// plays the audio at the actor's position 

	UGameplayStatics::PlaySoundAtLocation(this, AudioTunnelSFX, GetActorLocation());
	
}


void AAudioTunnels::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

