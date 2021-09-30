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
        SAFE_RELEASE(it->second);       // Image* �� �����Ҵ� ����
        it = mapImage.erase(it);             // ���� ������ �ּ�(iterator)�� ���ŵȴ�
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
//    // �߰��Ϸ��� �̹����� �ڷᱸ������ ã�´�.
//
//
//    // ã���� �ִ°� ��ȯ�Ѵ�.
//
//    
//    // ������ �߰��Ѵ�.
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

    SAFE_RELEASE(it->second);       // Image* �� �����Ҵ� ����
    mapImage.erase(it);             // �ʿ��� ��� ����

}
