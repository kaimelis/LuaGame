function OnEnable()

end

function OnDisable()

end

function OnCreate()
	Heal = Card.create("Heal", "Assets/Card_Health.png")
	Card.show(Heal, false)
	Info = {Damage = 0,Health=0,Mana = 5,Name="Heal",Description = "Restores 2 health"}
end