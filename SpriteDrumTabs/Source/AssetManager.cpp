#include "AssetManager.h"

#include <plog/Log.h>

/*static*/ sdt::AssetManager& sdt::AssetManager::Get()
{
	static AssetManager singletonInstance;
	return singletonInstance;
}

bool sdt::AssetManager::LoadDrumkitPieceTexture(const sdt::DrumkitPiece::Name& drumkitPieceName, const std::string& filepath)
{
	sf::Texture drumkitPieceTexture;
	if (drumkitPieceTexture.loadFromFile(filepath))
	{
		_drumkitPieceTextures.emplace(drumkitPieceName, drumkitPieceTexture);
		return true;
	}
	else
	{
		PLOG(plog::warning) << "Failed to load texture for " << drumkitPieceName << "at filepath" << filepath 
			<<". Rendering of this element will not work.";
		return false;
	}
}

bool sdt::AssetManager::LoadFont(const std::string& filepath)
{
	if (_font.loadFromFile(filepath))
	{
		PLOG(plog::info) << "Successfully loaded font from " << filepath << ".";
	}
	else
	{
		PLOG(plog::warning) << "Failed to load font from " << filepath << ". Text rendering will not work";
	}
}

bool sdt::AssetManager::LoadDrumkitPieceSound(const sdt::DrumkitPiece::Name& drumkitPieceName, const std::string& filepath)
{
	sf::SoundBuffer drumkitPieceSound;
	if (drumkitPieceSound.loadFromFile(filepath))
	{
		_drumkitPieceSoundBuffers.emplace(drumkitPieceName, drumkitPieceSound);
		return true;
	}
	else
	{
		PLOG(plog::warning) << "Failed to load sound for " << drumkitPieceName << "at filepath" << filepath
			<< ". Audio sample playback of this element will not work.";
		return false;
	}
}

const sf::Texture& sdt::AssetManager::GetDrumkitPieceTexture(const sdt::DrumkitPiece::Name& drumkitPieceName)
{
	const auto& drumkitPieceTextureIt = _drumkitPieceTextures.find(drumkitPieceName);
	if (drumkitPieceTextureIt == _drumkitPieceTextures.cend())
	{
		throw std::out_of_range("Tried to access the texture of " + drumkitPieceName + " but it was not found.");
	}
	else
	{
		//Such a stupid interface.
		return drumkitPieceTextureIt->second;
	}
}

const sf::Font& sdt::AssetManager::GetFont() const
{
	return _font;
}

const sf::SoundBuffer& sdt::AssetManager::GetDrumkitPieceSound(const sdt::DrumkitPiece::Name& drumkitPieceName)
{
	const auto& drumkitPieceSoundBufferIt = _drumkitPieceSoundBuffers.find(drumkitPieceName);
	if (drumkitPieceSoundBufferIt == _drumkitPieceSoundBuffers.cend())
	{
		throw std::out_of_range("Tried to access the audio sample of " + drumkitPieceName + " but it was not found.");
	}
	else
	{
		//Such a stupid interface.
		return drumkitPieceSoundBufferIt->second;
	}
}