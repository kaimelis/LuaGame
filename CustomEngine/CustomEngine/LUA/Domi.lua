function OnEnable()

end

function OnDisable()
	Card.doDamage(3)
end

function OnCreate()
	Domi = Card.create("Domi", "Assets/Card_Damage.png")
	Card.show(Domi, true)
	Info = {Damage = 1,Health=1,Mana = 1,Name="Domi",Description = "I do Nothing"}
end