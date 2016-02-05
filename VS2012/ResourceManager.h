#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include <vector>
#include "Exception.h"

namespace Game
{

	// items hold by ResourceManager
	// template to allow any types.
	template<class T>
	class ResourceItem
	{
	protected:
		T* _object;
	public:
		const T& GetObject() const
		{
			return *reinterpret_cast<T*>(_object);
		}
		virtual ~ResourceItem()
		{
		}
	};

	class TextureResourceItem : public ResourceItem<SDL_Texture>
	{
	protected:
		
	public:
		TextureResourceItem(const char* filename, SDL_Renderer* renderer)
		{
			SDL_Surface* image = SDL_LoadBMP(filename);
			if( image == NULL )
			{
				//TODO
				fprintf(stderr, "SDL Error: %s", SDL_GetError());
				throw new Exception::ApplicationException("TextureResourceItem error.");
			}
			//TODO  : is this correct for ALL textures?
			SDL_SetColorKey(image, 1, 255*65536 + 192*256 + 128);

			_object = SDL_CreateTextureFromSurface(renderer, image);
			SDL_FreeSurface(image);  // we got the texture now -> free surface
		}

		virtual ~TextureResourceItem()
		{
			SDL_DestroyTexture(_object);
		}
	};


	template<class T>
	class ResourceManager
	{
	protected:
		std::vector<ResourceItem<T>*> _object_list;

	public:
		ResourceManager() : _object_list()
		{
		}

		~ResourceManager()
		{
			for(unsigned int i=0; i<_object_list.size(); i++)
			{
				delete _object_list.at(i);
			}
			_object_list.clear();
		}

		// Any added object belong to the resource manager.
		// resource manager will delete items that are added here.
		void AddResource(const ResourceItem<T>& item)
		{
			_object_list.push_back((ResourceItem<T>*)(&item));
		}

		const T& GetResource(unsigned int index) const
		{
			return (T&)_object_list.at(index)->GetObject();
		}

	
	};



}

#endif