#pragma once

#include "DrumkitPiece.h"
#include "Globals.h"

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

BEGIN_SDT_NAMESPACE
class AssetManager
{
public:
	static AssetManager& Get();

	bool LoadDrumkitPieceTexture(const sdt::DrumkitPiece::Name& drumkitPieceName, const std::string& filepath);
	bool LoadFont(const std::string& filepath);
	bool LoadDrumkitPieceSound(const sdt::DrumkitPiece::Name& drumkitPieceName, const std::string& filepath);

	const sf::Texture& GetDrumkitPieceTexture(const sdt::DrumkitPiece::Name& drumkitPieceName);
	const sf::Font& GetFont() const;
	const sf::SoundBuffer& GetDrumkitPieceSound(const sdt::DrumkitPiece::Name& drumkitPieceName);

private:
	//Forces the class to behave as a singleton.
	AssetManager() = default;

	//Textures.
	std::map<sdt::DrumkitPiece::Name, sf::Texture> _drumkitPieceTextures;

	//Font.
	sf::Font _font;

	//Sounds.
	std::map<sdt::DrumkitPiece::Name, sf::SoundBuffer> _drumkitPieceSoundBuffers;
};
END_SDT_NAMESPACE