#include "Projectile.h"

#include "Player.h"
#include "GameScene.h"
#include "GameManager.h"

#include "Enemy.h"
#include <iostream>

Projectile::Projectile(float width, float height, int layer, const Color& color, bool hasCollision, Scene* pScene) : Entity(width, height, layer, hasCollision, color, pScene)
{
    // ShowCollision(true);
}

Projectile::Projectile(float width, float height, int layer, Scene* pScene) : Entity(width, height, layer, true, Color::Red, pScene) {}

void Projectile::OnUpdate()
{
    Player* player = GetScene<GameScene>()->pPlayer;
    GameScene* scene = GetScene<GameScene>();
    int ratio = GetScene<GameScene>()->ratio;
    bool pGameReset = GetScene<GameScene>()->m_gameReset;
    
    if (pGameReset)
    {
        Destroy();
    }

    if (GetPosition().m_x > scene->GetWindowWidth() || GetPosition().m_x < 0 || GetPosition().m_y < 0 || GetPosition().m_y > scene->GetWindowHeight())
    {
        Destroy();
    }
    if (projEnemyLaser)
    {
        m_tempTime += GetScene<GameScene>()->GetDeltaTime();
        
        if (m_destroyProjectileTimer < m_tempTime)
        {
            Destroy();
        }
    } 
    if (projBossLaser)
    {
        m_tempTime += GetScene<GameScene>()->GetDeltaTime();

        if (m_destroyProjectileTimer < m_tempTime)
        {
            Destroy();
        }
    }
    if (proj2)
    {
       if ((GetPosition().m_y > m_positionInitialY + 100 || GetPosition().m_y < m_positionInitialY - 60) 
           && GetPosition().m_x < m_positionInitialX + 100
           && proj2HaveTarget == false)
        {
           SetSpeed(500.0f);    
           SetDirection(1, 0, GetSpeed());
           SetCollisionSize(m_colisionSize, m_colisionSize);
       }
       if (proj2HaveTarget)
       {
           SetSpeed(500.0f);
           GoToPosition(positionEnemyX, positionEnemyY, GetSpeed());
       }
       if (GetPosition().m_x == positionEnemyX && GetPosition().m_y == positionEnemyY)
       {
           Destroy();
       }
    }
    if (projUltimate)
    {
        m_tempTime += GetScene<GameScene>()->GetDeltaTime();

        GoToPosition(player->GetPosition().m_x + (player->GetWidth() * 7), player->GetPosition().m_y, 750.0f);
        if (m_destroyProjectileTimer < m_tempTime)
        {
            Destroy();
        }
    }
}

void Projectile::OnCollision(Entity* collidedWith)
{
    if (collidedWith->IsTag(GameScene::Tag::PLAYER) && projEnemy == true)
    {
        Destroy();
    }
    if (collidedWith->IsTag(GameScene::Tag::ENEMY) && proj2 == true )
    {
        proj2HaveTarget = true;
        positionEnemyX = collidedWith->GetPosition().m_x;
        positionEnemyY = collidedWith->GetPosition().m_y;
        m_colisionSize = m_colisionSize - 50;
        SetCollisionSize(m_colisionSize);

        if (m_colisionSize < 100)
        {
            SetTag(GameScene::PROJECTILETETECHERCHEUSE);
        }
    }
}

void Projectile::ShootProjectile1(Entity* player)
{
    SetPosition(player->GetPosition().m_x + (player->GetWidth() * 0.7), player->GetPosition().m_y);
    SetSpeed(700.0f);
    GoToDirection(GetPosition().m_x + 1, GetPosition().m_y, GetSpeed());
}

void Projectile::ShootProjectile2(Entity* player)
{
    int ratio = GetScene<GameScene>()->ratio;

    proj2 = true;
    SetPosition(player->GetPosition().m_x, player->GetPosition().m_y + (player->GetHeight() * 0.7));
    m_positionInitialY = GetPosition().m_y;
    m_positionInitialX = GetPosition().m_x;
    SetSpeed(125.0f);
    SetDirection(0, 1, GetSpeed());

    pProjectile2 = CreateEntity<Projectile>(20 * ratio, 20 * ratio, 6, Color::Pink);
    pProjectile2->proj2 = true;
    pProjectile2->SetPosition(player->GetPosition().m_x, player->GetPosition().m_y - (player->GetHeight() ));
    pProjectile2->m_positionInitialY = pProjectile2->GetPosition().m_y;
    pProjectile2->m_positionInitialX = pProjectile2->GetPosition().m_x;
    pProjectile2->SetSpeed(125.0f);
    pProjectile2->SetDirection(0, -1, pProjectile2->GetSpeed());
    pProjectile2->PlayAnimation("MissileBleu");
    pProjectile2->SetScale(0.25f, 0.25f);
    pProjectile2->SetCollisionSize(600.f, 600.f);
}

void Projectile::DestroyProjectile3()
{
    Destroy();
}

void Projectile::ShootProjectileEnemy1(Entity* enemy)
{
    projEnemy = true;
    SetPosition(enemy->GetPosition().m_x - 1, enemy->GetPosition().m_y);
    SetSpeed(500.0f);
    SetDirection(-1, 0, GetSpeed());
}

void Projectile::ShootProjectileEnemy3Laser(Entity* enemy)
{
    projEnemyLaser = true;
    SetPosition(enemy->GetPosition().m_x, enemy->GetPosition().m_y + GetScene<GameScene>()->GetWindowHeight() * 0.5);
}

void Projectile::ShootProjectileBossLaser(Entity* enemy)
{
    projBossLaser = true;
    SetPosition(enemy->GetPosition().m_x - GetScene<GameScene>()->GetWindowWidth() * 0.5, enemy->GetPosition().m_y);
}