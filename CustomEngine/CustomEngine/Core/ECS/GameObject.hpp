#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "SFML/Graphics.hpp"

class GameObject
{
public :
	GameObject(sf::Sprite pSprite, sf::Texture pTexture, std::string pDirectory, std::string pName);
	~GameObject();
	sf::Sprite GetSprite();
	sf::Texture GetTexture();
	std::string GetName();
	std::string GetDirectory();
	sf::Vector2f GetPosition();

	sf::Text GetDamageText();
	sf::Text GetHealthText();
	sf::Text GetManaText();
	sf::Text GetDescriptionText();
	sf::Text GetNameText();

	void SetTextPosition();

	int GetDamage();
	int GetHealth();
	int GetMana();
	bool GetIsOnBoard();
	
	void SetTexture(sf::Texture pTexture);
	void SetSprite(sf::Sprite pSprite);
	void Scale(sf::Vector2f pScale);
	void SetPosition(sf::Vector2f pPosition);

	void SetDamage(int pDamage);
	void SetHealth(int pHealth);
	void SetManaCost(int pManaCost);
	void SetDescription(std::string pDescription);
	void SetIsOnBoard(bool pIsOnBoard);

	void MakeDamage(int pDamage);
	void AddHealth(int pHealth);

	sf::Text _damageText;
	sf::Text _healthText;
	sf::Text _manaText;
	sf::Text _descriptionText;
	sf::Text _nameText;
	sf::Vector2f _position;
	void DestroyCard();

private:

	sf::Sprite _sprite;
	sf::Texture _texture;
	std::string _name;
	std::string _directory;
	std::string _description;
	
	int _damage;
	int _health;
	int _manaCost;
	bool _isOnBoard = false;
};

#endif //GAMEOBJECT_HPP