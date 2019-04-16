function OnEnable()

end

function OnDisable()

end

function OnCreate()
	Eadweard = Card.create("Eadweard", "Assets/Card_Damage.png")
	Card.show(Eadweard, false)
	Info = {Damage = 2,Health=1,Mana = 2,Name="Eadweard",Description = "I do Nothing"}
end