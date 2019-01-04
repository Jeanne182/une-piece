#ifndef ASSET_MANAGER_UP_HPP__
#define ASSET_MANAGER_UP_HPP__

#include <string>
#include <map>

#include <glimac/common.hpp>
#include <glimac/FilePath.hpp>

#include <class/ScoresManager.hpp>
#include <class/TextManager.hpp>
#include <class/Program.hpp>
#include <class/Model.hpp>
#include <class/Error.hpp>

using namespace glimac;

namespace UP
{

/**
 * @brief Single Class
 * @brief Create the AssetManager Object that serves as a facade for all the OpenGL stuff
 *
 */
class AssetManager
{
public:
  /**
   * @brief Create the Singleton
   *
   * @param argv
   * @return AssetManager&
   */
  static void Create(char **argv)
  {
    if (!instance) // Only allow one instance of class to be generated.
      instance = new AssetManager(argv);
    instance->_textManager.setupTTF();
  };

  /**
   * @brief Get the Singleton
   * 
   * @return AssetManager& 
   */
  static AssetManager *Get()
  {
    if (!instance)
      throw Error("No instance given", AT);
    return instance;
  }

  /**
   * @brief Get the Save file
   * 
   * @param fileName 
   * @return std::string 
   */
  std::string saveFile(const std::string &fileName) const;

  /**
   * @brief Get a Model file
   * 
   * @param model 
   * @return std::string 
   */
  std::string modelFile(const std::string &model) const;

  /**
   * @brief Get a Texture file
   * 
   * @param texture 
   * @return std::string 
   */
  std::string textureFile(const std::string &texture) const;

  /**
   * @brief Get a font file
   * 
   * @param file 
   * @return std::string 
   */
  std::string fontFile(const std::string &font) const;

  /**
   * @brief Return a Model
   * 
   * @param name 
   * @return const Model& 
   */
  Model *model(const std::string &name);

  /**
   * @brief Return a Model
   * 
   * @param name 
   * @return const Model& 
   */
  Model *model(const std::string &name) const;

  /**
   * @brief Get the Asset Program
   * 
   */
  inline const AssetProgram &assetProgram() const { return _assetProgram; };

  /**
   * @brief Get the Asset ProgramMulti
   * 
   */
  inline const AssetProgramMulti &assetProgramMulti() const { return _assetProgramMulti; };

  /**
   * @brief Get the Asset ProgramMultiLight
   * 
   */
  inline const AssetProgramMultiLight &assetProgramMultiLight() const { return _assetProgramMultiLight; };

  /**
   * @brief Get the Static Image Program
   * 
   */
  inline const StaticImageProgram &staticImageProgram() const { return _staticImageProgram; };

  /**
   * @brief Get the Glyph Program
   * 
   * @return const GlyphProgram& 
   */
  inline const GlyphProgram &glyphProgram() const { return _glyphProgram; };

  /**
   * @brief Get the Skybox Program
   * 
   * @return const SkyboxProgram& 
   */
  inline const SkyboxProgram &skyboxProgram() const { return _skyboxProgram; };

  /**
   * @brief Get the Text Manager
   * 
   * @return const TextManager& 
   */
  inline TextManager &textManager() { return _textManager; };

private:
  /**
   * @brief Construct a new AssetManager object
   *
   * @param appPath
   * @param width
   * @param height
   */
  AssetManager(char **argv)
      : _appPath(argv[0]),
        _assetProgram(_appPath),
        _assetProgramMulti(_appPath),
        _assetProgramMultiLight(_appPath),
        _staticImageProgram(_appPath),
        _skyboxProgram(_appPath),
        _glyphProgram(_appPath){};

  // AssetManager Path
  FilePath _appPath;

  // Programs
  AssetProgram _assetProgram;
  AssetProgramMulti _assetProgramMulti;
  AssetProgramMultiLight _assetProgramMultiLight;
  StaticImageProgram _staticImageProgram;
  SkyboxProgram _skyboxProgram;
  GlyphProgram _glyphProgram;

  // TextManager
  TextManager _textManager;

  // Models
  std::map<std::string, Model *> _models;

  // ================ SINGLETON's STUFF ==============
  static AssetManager *instance;
  AssetManager() = delete;
  AssetManager(AssetManager const &) = delete;
  void operator=(AssetManager const &) = delete;
};

} // namespace UP

#endif // ASSET_MANAGER_UP_HPP__
