#ifndef __CPARTICLE_SYSTEM_H__
#define __CPARTICLE_SYSTEM_H__

#include "cocos2d.h"
#include "CParticle.h"
#include <list>

using namespace std;


class CParticleSystem
{
private:
	CParticle* _pParticles;
	list<CParticle*> _FreeList;
	list<CParticle*> _InUsedList;
	int _iFree;	// 可用的  Particle 個數
	int _iInUsed;  // 正在使用的 Particle 個數
	int _iType;  // 目前控制的分子運動模式是哪一種型態

	bool _bEmitterOn; // Emitter 是否顯示

public:
	// Emitter 設定的相關參數
	cocos2d::Point _emitterPt;// Emitter 的位置	
	float    _fDir; // Emitter 的噴射方向，0 到 360度，逆時針方向為正
	int		_iNumParticles;	// 每秒鐘產生的分子個數
	int     _iGenParticles; // 到目前為止所產生的分子個數(以每秒為單位)
	float	_fSpread;	 // 0 到 180 度，預設為 180 
	float   _fVelocity;	 // 分子的離開速度
	float   _fLifeTime;	 // 分子的存活時間
	float	_fSpin;		// 分子的旋轉量 degree/sec
	float   _fGravity;
	float   _fOpacity;  //分子的透明度
	float   _fElpasedTime;	// 經過多少時間，以秒為單位，作為成生分子的計算依據
	cocos2d::Point _windDir;  // 風的方向，本範例沒有實作
	cocos2d::Color3B _color;	// 分子的顏色
	CParticleSystem();
	~CParticleSystem();
	void init(cocos2d::Layer &inlayer);
	void doStep(float dt);
	void setEmitter(bool bEm);
	void setType(int type) { _iType = type; }

 //   void onTouchesEnded(const cocos2d::CCPoint &touchPoint);
    void onTouchesBegan(const cocos2d::CCPoint &touchPoint);
    void onTouchesMoved(const cocos2d::CCPoint &touchPoint);

	void setGravity(float fGravity);
	void setOpacity(float fOpacity);
	void setNumParticles(int iNumParticles);
	void setSpeed(float fSpeed);
	void setWind(float fWind);

	void setBubble(cocos2d::Layer &inlayer);
	void setCircle(cocos2d::Layer &inlayer);
	void setCloud(cocos2d::Layer &inlayer);
	void setComet(cocos2d::Layer &inlayer);
	void setFlare(cocos2d::Layer &inlayer);
	void setRain(cocos2d::Layer &inlayer);
	void setSpark(cocos2d::Layer &inlayer);

};

#endif