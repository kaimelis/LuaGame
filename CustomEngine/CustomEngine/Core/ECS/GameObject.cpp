#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject(sf::Sprite pSprite, sf::Texture pTexture, std::string pDirectory, std::string pName) : _sprite(pSprite),_texture(pTexture), _directory(pDirectory), _name(pName)
{
	_texture.loadFromFile(_directory);
	_sprite.setTexture(_texture);
}
GameObject::~GameObject()
{}


void GameObject::SetTextPosition() 
{
	_damageText.setCharacterSize(30);
	_healthText.setCharacterSize(30);
	_damageText.setCharacterSize(30);
	_manaText.setCharacterSize(30);
	_descriptionText.setCharacterSize(15);
	_nameText.setCharacterSize(30);

	_healthText.setStyle(sf::Text::Bold);
	_damageText.setStyle(sf::Text::Bold);
	_manaText.setStyle(sf::Text::Bold);
	_nameText.setStyle(sf::Text::Bold);

	_healthText.setString(std::to_string(_health));
	_damageText.setString(std::to_string(_damage));
	_manaText.setString(std::to_string(_manaCost));
	_descriptionText.setString(_description);
	_nameText.setString(_name);

	sf::FloatRect textRect = _damageText.getLocalBounds();
	_damageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	_damageText.setPosition(_sprite.getPosition().x + (_sprite.getTextureRect().width / 7), _sprite.getPosition().y + (_sprite.getTextureRect().height * 0.88f));

	sf::FloatRect textRect2 = _healthText.getLocalBounds();
	_healthText.setOrigin(textRect2.left + textRect2.width / 2.0f, textRect2.top + textRect2.height / 2.0f);
	_healthText.setPosition(_sprite.getPosition().x - (_sprite.getTextureRect().width / 8), _sprite.getPosition().y + (_sprite.getTextureRect().height * 0.88f));

	sf::FloatRect textRect3 = _manaText.getLocalBounds();
	_manaText.setOrigin(textRect3.left + textRect3.width / 2.0f, textRect3.top + textRect3.height / 2.0f);
	_manaText.setPosition(GetPosition().x / 8, GetPosition().y);
	_manaText.setPosition(_sprite.getPosition().x + (_sprite.getTextureRect().width / 8), _sprite.getPosition().y + (_sprite.getTextureRect().height / 8));

	sf::FloatRect textRect4 = _nameText.getLocalBounds();
	_nameText.setOrigin(textRect4.left + textRect4.width / 2.0f, textRect4.top + textRect4.height / 2.0f);
	_nameText.setPosition(_sprite.getPosition().x +( _sprite.getTextureRect().width/2), _sprite.getPosition().y + (_sprite.getTextureRect().height / 2));

	sf::FloatRect textRect5 = _descriptionText.getLocalBounds();
	_descriptionText.setOrigin(textRect5.left + textRect5.width / 2.0f, textRect5.top + textRect5.height / 2.0f);
	_descriptionText.setPosition(_sprite.getPosition().x + (_sprite.getTextureRect().width / 2), _sprite.getPosition().y + (_sprite.getTextureRect().height / 1.4f));

}

sf::Text GameObject::GetDamageText()
{
	return _damageText;
}

sf::Text GameObject::GetHealthText()
{
	return _healthText;
}

sf::Text GameObject::GetManaText()
{
	return _manaText;
}

sf::Text GameObject::GetDescriptionText()
{
	return _descriptionText;
}

sf::Text GameObject::GetNameText()
{
	return _nameText;
}

void GameObject::SetDescription(std::string pDescription)
{
	_description = pDescription;
}

void GameObject::MakeDamage(int pDamage)
{
	_health -= pDamage;
}

void GameObject::AddHealth(int pHealth)
{
	_health += pHealth;
}

void GameObject::SetTexture(sf::Texture pTexture)
{
	_texture = pTexture;
}

void GameObject::SetSprite(sf::Sprite pSprite)
{
	_sprite = pSprite;
}

void GameObject::Scale(sf::Vector2f pScale)
{
	_sprite.scale(pScale);
}

void GameObject::SetPosition(sf::Vector2f pPosition)
{
	SetTextPosition();
	_sprite.setPosition(pPosition);
}

void GameObject::SetIsOnBoard(bool pIsOnBoard)
{
	_isOnBoard = pIsOnBoard;
}

void GameObject::SetDamage(int pDamage) 
{
	_damage = pDamage;
}
void GameObject::SetManaCost(int pMana)
{
	_manaCost = pMana;
}
void GameObject::SetHealth(int pHealth)
{
	_health = pHealth;
}

sf::Vector2f GameObject::GetPosition()
{
	return _sprite.getPosition();
}

sf::Sprite GameObject::GetSprite()
{
	return _sprite;
}

sf::Texture GameObject::GetTexture()
{
	return _texture;
}

std::string GameObject::GetName()
{
	return _name;
}

bool GameObject::GetIsOnBoard()
{
	return _isOnBoard;
}

int GameObject::GetDamage()
{
	return _damage;
}

int GameObject::GetHealth()
{
	return _health;
}

int GameObject::GetMana()
{
	return _manaCost;
}

void GameObject::DestroyCard()
{
	delete this;
}