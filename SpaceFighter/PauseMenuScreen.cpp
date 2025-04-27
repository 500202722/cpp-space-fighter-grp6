#include "PauseMenuScreen.h"
#include "MainMenuScreen.h"

PauseMenuScreen::PauseMenuScreen(GameplayScreen * GameplayScreen) {
	m_pGameplayScreen = GameplayScreen;
	SetTransitionInTime(0.5f);
	SetTransitionOutTime(0.5f);

	Show();
}

void PauseMenuScreen::HandleInput(const InputState & input) {
	if (input.IsNewKeyPress(Key::ESCAPE)) GetMenuItem(RESUME_GAME)->Select(this);
	else MenuScreen::HandleInput(input);
}

void PauseMenuScreen::LoadContent(ResourceManager & resourceManager)
{
	// Logo
	m_pTexture = resourceManager.Load<Texture>("Textures\\Logo.png");
	m_texturePosition = Game::GetScreenCenter() - Vector2::UNIT_Y * 150;

	// Create the menu items
	const int COUNT = 3;
	MenuItem * pItem;
	Font::SetLoadSize(20, true);
	Font * pFont = resourceManager.Load<Font>("Fonts\\arial.ttf");

	SetDisplayCount(COUNT);

	std::string text[COUNT] = { "Resume Game", "Main Menu", "Quit to Desktop" };

	for (int i = 0; i < COUNT; i++)
	{
		pItem = new MenuItem(text[i]);
		pItem->SetPosition(Vector2(100, 100 + 50 * i));
		pItem->SetFont(pFont);
		pItem->SetColor(Color::BLUE);
		pItem->SetSelected(i == 0);
		AddMenuItem(pItem);
	}

	// when "Start Game" is selected, replace the "SetRemoveCallback" delegate
	// so that it doesn't quit the game (originally set in the constructor)
	GetMenuItem(RESUME_GAME)->SetOnSelect([this]() {
		Exit();
		});
	GetMenuItem(MAIN_MENU)->SetOnSelect([this]() {
		SetOnRemove([this]() { 
			AddScreen(new MainMenuScreen());
			m_pGameplayScreen->Exit(); 
		});
		Exit();
	});

	// bind the Exit method to the quit menu item
	GetMenuItem(QUIT)->SetOnSelect([this]() {
		SetOnRemove([this]() { GetGame()->Quit(); });
		Exit();
	});
}

void PauseMenuScreen::Update(const GameTime & gameTime)
{
	bool isSelected = false;
	float alpha = GetAlpha();
	float offset = sinf(gameTime.GetTotalTime() * 10) * 5 + 5;

	for (MenuItem * pItem : GetMenuItems())
	{
		pItem->SetAlpha(alpha);
		isSelected = pItem->IsSelected();
		pItem->SetColor(isSelected ? Color::WHITE : Color::RED);
		pItem->SetTextOffset(isSelected ? Vector2::UNIT_X * offset : Vector2::ZERO);
	}

	MenuScreen::Update(gameTime);
}

void PauseMenuScreen::Draw(SpriteBatch & spriteBatch)
{
	spriteBatch.Begin();
	spriteBatch.Draw(m_pTexture, m_texturePosition, Color::WHITE * GetAlpha(), m_pTexture->GetCenter());
	MenuScreen::Draw(spriteBatch);
	spriteBatch.End();
}
