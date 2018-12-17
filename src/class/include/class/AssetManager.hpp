#ifndef ASSET_MANAGER_UP_HPP__
#define ASSET_MANAGER_UP_HPP__

#include <string>

#include <glimac/common.hpp>
#include <glimac/FilePath.hpp>

#include <class/Program.hpp>
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
   * @param modelName 
   * @return std::string 
   */
  std::string model(const std::string &model) const;

  /**
   * @brief Get A texture
   * 
   * @param modelName 
   * @return std::string 
   */
  std::string texture(const std::string &texture) const;

  /**
   * @brief Get the Asset Program
   * 
   */
  inline const AssetProgram &assetProgram() const { return _assetProgram; };

  /**
   * @brief Get the Asset Program
   * 
   */
  inline const StaticImageProgram &staticImageProgram() const { return _staticImageProgram; };

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
        _staticImageProgram(_appPath){};

  // AssetManager Path
  FilePath _appPath;

  // Programs
  AssetProgram _assetProgram;
  StaticImageProgram _staticImageProgram;

  // ================ SINGLETON's STUFF ==============
  static AssetManager *instance;
  AssetManager() = delete;
  AssetManager(AssetManager const &) = delete;
  void operator=(AssetManager const &) = delete;
};

} // namespace UP

#endif // ASSET_MANAGER_UP_HPP__
