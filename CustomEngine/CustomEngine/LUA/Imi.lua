function OnEnable()

end

function OnDisable()

end

function OnCreate()
	Imi = Card.create("Imi", "Assets/Card_Damage.png")
	Card.show(Imi, true)
	Info = {Damage = 1,Health=1,Mana = 1,Name="Imi",Description = "I do Nothing"}
end