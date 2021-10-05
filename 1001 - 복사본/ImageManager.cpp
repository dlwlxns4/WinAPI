#include "ImageManager.h"
#include "Image.h"

void ImageManager::Init()
{
}



void ImageManager::Release()
{
    map<string, Image*>::iterator it;
    for (it = mapImage.begin(); it != mapImage.end(); )
    {
        SAFE_RELEASE(it->second);       // Image* 의 동적할당 해제
        it = mapImage.erase(it);             // 다음 원소의 주소(iterator)가 갱신된다
    }
    mapImage.clear();

}

void ImageManager::AddImage(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
    if (FindImage(fileName))
    {
        return;
    }

    Image* image = new Image;
    if (FAILED(image->Init(fileName, width, height, isTrans, transColor)))
    {
        SAFE_RELEASE(image);
        return;
    }

    mapImage.insert(make_pair(fileName, image));
}

void ImageManager::AddImage(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
    if (FindImage(fileName))
    {
        return;
    }

    Image* image = new Image;
    if (FAILED(image->Init(fileName, width, height,maxFrameX, maxFrameY, isTrans, transColor)))
    {
        SAFE_RELEASE(image);
        return;
    }

    mapImage.insert(make_pair(fileName, image));
}

//void ImageManager::AddImage()
//{
//    // 추가하려는 이미지를 자료구조에서 찾는다.
//
//
//    // 찾으면 있는걸 반환한다.
//
//    
//    // 없으면 추가한다.
//
//
//}

Image* ImageManager::FindImage(const char* fileName)
{
    map<string, Image*>::iterator it =mapImage.find(fileName);
    if (it == mapImage.end())
    {
        return nullptr;
    }

    return it->second;
}

void ImageManager::DeleteImage(const char* fileName)
{
    map<string, Image*>::iterator it = mapImage.find(fileName);
    if (it == mapImage.end())
        return;

    SAFE_RELEASE(it->second);       // Image* 의 동적할당 해제
    mapImage.erase(it);             // 맵에서 노드 삭제

}
