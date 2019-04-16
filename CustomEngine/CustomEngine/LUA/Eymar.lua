function OnEnable()

end

function OnDisable()

end

function OnCreate()
	Eymar = Card.create("Eymar", "Assets/Card_Damage.png")
	Card.show(Eymar, false)
	Info = {Damage = 3,Health=4,Mana = 6,Name="Eymar",Description = "I do Nothing"}
end