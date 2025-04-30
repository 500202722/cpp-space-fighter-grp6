#pragma once

#include "Weapon.h"

class PlasmaBomb : public Weapon
{

public:

	PlasmaBomb(const std::string& key) : Weapon(key) {}
	virtual ~PlasmaBomb() {}

	virtual void Update(const GameTime& gameTime);

	/** @brief Check if the blaster is ready to fire.
		@return True if the blaster is ready to fire. */
	virtual bool CanFire() const { return m_cooldown <= 0; }

	/** Reset the cooldown of the special attack. */
	virtual void ResetCooldown() { m_cooldown = 3.5; }

	/** @brief Get the number of seconds the blaster must wait between shots.
		@return The number of seconds the blaster must wait between shots. */
	virtual float GetCooldownSeconds() { return m_cooldownSeconds; }

	/** @brief Set the number of seconds the blaster must wait between shots.
		@param seconds The number of seconds the blaster must wait between shots. */
	virtual void SetCooldownSeconds(const float seconds) { m_cooldownSeconds = seconds; }

	/** @brief Fire the blaster.
		@param triggerType The type of trigger that fired the weapon.
		@remark If the triggerType doesn't match that of the Blaster, the command will be ignored. */
	virtual void Fire(TriggerType triggerType);

	virtual float GetAOEAttackRadius() const { return m_aoeRadius;}

	virtual void SetAOEAttackRadius(const float radius) { m_aoeRadius = radius; }

private:

	float m_cooldown = 3.5;
	float m_cooldownSeconds = 5.5;
	float m_aoeRadius = 200;

};