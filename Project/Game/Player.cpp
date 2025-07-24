#include "Player.h"

Player::Player(const string& texturePath, Vector2f pos, int left, int top, int width, int height) : sprite(texture)
{
	if (!texture.loadFromFile("Assets/player.png"))
	{
		cerr << "에러 : player 스프라이트 찾을 수 없음." << endl;
		return;
	}
	IntRect rectI = { {left,top},{width,height} };
	FloatRect rectF =
	{
	  {static_cast<Vector2f>(rectI.position)},
	  { static_cast<Vector2f>(rectI.size)}
	};

	sprite.setTextureRect(rectI);
	sprite.setOrigin({ rectF.size.x / 2.f,rectF.size.y / 2.f });
	hitBoxSize = rectF.size;
	senceBoxSize = {300.f, 300.f };

	SetPlayerPos(pos);

}

void Player::Update(float deltaTime)
{
	Move(deltaTime);
	CrowdControlUpdate(deltaTime);
}

void Player::SetPlayerPos(Vector2f pos)
{
	sprite.setPosition(pos);
	Updatehitbox();
	UpdatesenseBox();
}

void Player::Updatehitbox()
{
	Vector2f worldPos = sprite.getPosition();
	Vector2f origin = sprite.getOrigin();
	Vector2f criteria = worldPos - origin;

	hitBox = { criteria , hitBoxSize };
}

void Player::UpdatesenseBox()
{
	Vector2f worldPos = sprite.getPosition(); 
	Vector2f criteria = worldPos - (senceBoxSize/2.f);

	senceBox = { criteria, senceBoxSize };
}

void Player::CrowdControlUpdate(float deltaTime)
{
	if (CrowdControl)
	{
		CrowdControlTimer -= deltaTime;
		if (CrowdControlTimer <= 0.f)
		{
			CrowdControl = false;
		}
	}
	
}

void Player::SetCrowdControlTimer(float time)
{
	CrowdControlTimer = time;
}

void Player::UpdateAnimation()
{

}

void Player::UpdateState()
{
	if (!IsOnGround) // 점프할 때
	{
		currentState = PlayerState::Jumping;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Scan::A) && sprite.getPosition().x > 0) // 왼쪽 키 누를 때
	{
		currentState = PlayerState::L_Running;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Scan::D) && sprite.getPosition().x < 600) // 오른쪽 키 누를 때
	{
		currentState = PlayerState::R_Running;
	}
	else // 아무것도 안 할 때
	{
		currentState = PlayerState::Idle;
	}
}

void Player::Draw(RenderWindow& window)
{
	window.draw(sprite);
}

// 인식 범위에 있는 맵 좌표를 그리드 좌표로 반환하는 함수
vector<pair<int, int>> Player::GetnearGridcells()
{
	vector<pair<int, int>> neargirdcells;

	float left = senceBox.position.x;
	float top = senceBox.position.y;
	float right = senceBox.position.x + senceBox.size.x;
	float bottom = senceBox.position.y + senceBox.size.y;

	float cellsize = 100.f;

	int gridleft = static_cast<int>(floor(left / cellsize));
	int gridright = static_cast<int>(floor(right / cellsize));
	int gridtop = static_cast<int>(floor(top / cellsize));
	int gridbottom = static_cast<int>(floor(bottom / cellsize));

	for (int y = gridtop; y <= gridbottom ; y++)
	{
		for (int x = gridleft; x <= gridright; x++)
		{
			neargirdcells.emplace_back(x, y);
		}
	}
	return neargirdcells;
}

FloatRect& Player::GetSenseBox()
{
	return senceBox;
}
Vector2f Player::GetPlayerPos()
{
	return sprite.getPosition();
}

FloatRect& Player::GetHitBox()
{
	return hitBox;
}

void Player::Move(float deltaTime)
{

	bool jumpKey = Keyboard::isKeyPressed(Keyboard::Scan::Space);

	if (jumpKey)
	{
		if (IsOnGround)
		{
			velocityY = -300.f;
			IsOnGround = false;
		}

	}
	
	//if (!IsOnGround)
	//{
	//	velocityY += GRAVITY * deltaTime;
	//	sprite.move({ 0.0f, velocityY * deltaTime });
	//}
	//else
	//{
	//	velocityY = 0.f;
	//}
	

	if (Keyboard::isKeyPressed(Keyboard::Scan::Left) && sprite.getPosition().x > 900)
	{
		sprite.move({ -200.0f * deltaTime ,0.0f });
		sprite.setTextureRect(IntRect({ 0,0 }, { 50,50 }));
		sprite.setScale({ -1.0f, 1.0f });
	}
	if (Keyboard::isKeyPressed(Keyboard::Scan::Right) && sprite.getPosition().x < 1700)
	{
		sprite.move({ 200.0f * deltaTime ,0.0f });
		sprite.setTextureRect(IntRect({ 0,0 }, { 50,50 }));
		sprite.setScale({ 1.0f, 1.0f });

	}
	if (Keyboard::isKeyPressed(Keyboard::Scan::Up))
	{
		sprite.move({ 0.0f,  -200.f * deltaTime });
	}
	if (Keyboard::isKeyPressed(Keyboard::Scan::Down))
	{
		sprite.move({ 0.0f,  200.f * deltaTime });
	}
	cout <<"x:" << sprite.getPosition().x << " " << "y:" << sprite.getPosition().y << endl;
	Updatehitbox();
	UpdatesenseBox();
}


