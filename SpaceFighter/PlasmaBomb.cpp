#include "Level.h"
#include "PlasmaBomb.h"

void PlasmaBomb::Update(const GameTime& gameTime)
{
        if (m_cooldown > 0) m_cooldown -= gameTime.GetElapsedTime();
}

void PlasmaBomb::Fire(TriggerType triggerType)
{
        if (!IsActive()) return;
        if (!CanFire()) return;
        if (!triggerType.Contains(GetTriggerType())) return; 

        float shots = 60;
        for (float i = 0; i < shots; i++)
        {
        // Shoot 60 shots 360 degrees around ship
        Projectile* pProjectile = (GetProjectile());
        if (!pProjectile) return;

        float projectileDirection = (Math::PI * 2 * (i / shots));
        float x = std::cos(projectileDirection);
        float y = std::sin(projectileDirection);

        pProjectile->SetDirection(Vector2(x, y));
        pProjectile->Activate(GetPosition(), IsAttachedToPlayer());
        }
        AudioSample* pAudio = GetFireSound();
        if (pAudio) pAudio->Play();
        
        m_cooldown = m_cooldownSeconds;
}

