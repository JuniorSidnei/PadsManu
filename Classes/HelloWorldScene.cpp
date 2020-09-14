/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include <iostream>
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#define BACKGROUND_MUSIC_SFX  "background-music-aac.mp3"
#define PEW_PEW_SFX "pew-pew-lei.mp3"

const char *fontName = "fonts/Uni Sans Heavy.otf";


USING_NS_CC;

Scene *HelloWorld::createScene() {
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {

    if (!Scene::init()) {
        return false;
    }

    _groot = GRoot::create(this);
    _groot->retain();

    continueInit();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto kitLabel = Label::createWithTTF("KIT", fontName, 50);
    kitLabel->setTextColor(Color4B::GRAY);
    kitLabel->setPosition(250, 1400);
    this->addChild(kitLabel, 2);

    auto nameLabel = Label::createWithTTF("NAME", fontName, 50);
    nameLabel->setPosition(350, 1400);
    this->addChild(nameLabel, 2);

    // add background
    auto bg = DrawNode::create();
    bg->drawSolidRect(origin, visibleSize, Color4F(0.14, 0.16, 0.18, 1));
    this->addChild(bg, 0);

    //add bg to menu
    auto menuBg = Sprite::create("menuBg.png");
    menuBg->setPosition(100, 1400);
    this->addChild(menuBg);


    //add pads
    generatePads(4, 3);

    //add bg music
    //SimpleAudioEngine().getInstance()->playBackgroundMusic(BACKGROUND_MUSIC_SFX, true);

    return true;
}

MenuItemImage *HelloWorld::createPad(const Vec2 &position, std::string buttonsColors) {
    auto padButton = MenuItemImage::create(buttonsColors, buttonsColors, [&](Ref *sender) {
        SimpleAudioEngine().getInstance()->playEffect(PEW_PEW_SFX);
    });
    padButton->setPosition(position);
    return padButton;
}

cocos2d::Vec2 HelloWorld::getOrigin() {
    return Director::getInstance()->getVisibleOrigin();
}

void HelloWorld::generatePads(int padAmountLine, int padAmountCollum) {

    for (int y = 0; y < padAmountLine; y++) {

        for (int x = 0; x < padAmountCollum; x++) {
            float padX, padY;
            padX = 148 + (266 * x);
            padY = 1094 - (266 * y);
            this->addChild(createPad(Vec2(padX, padY), HelloWorld::buttonColors[y]));
        }
    }
}
