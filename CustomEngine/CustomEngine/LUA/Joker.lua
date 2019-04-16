function OnEnable()

end

function OnDisable()

end

function OnCreate()
	Joker = Card.create("Joker", "Assets/Card_Damage.png")
	Card.show(Joker, true)
	Info = {Damage = 3,Health=3,Mana = 4,Name="Joker",Description = "I do Nothing"}
end